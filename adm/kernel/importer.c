// importer.c
// 用户档案导入器

#include <ansi.h>

inherit ITEM;
inherit F_SAVE;

#define SAVE_DIR        "/data.3k/"
#define SUFFIX_NAME     "fr"
#define SUFFIX_SIZE     26

// 日志等级分为 3 级，如何界定一段消息应该记录在
// 哪一级的日志中？

// LV 1: 无法复制文件、载入用户等错误信息
// LV 2: 对用户有损的删除一类的操作信息
// LV 3: 复制或者修改这样的无损操作信息

#define LOG_LEVEL       3
#define LOG(lv, msg)    log_file(sprintf("transfer/LV%d", lv), msg);

// 奇怪的是 'nosave' 关键字不许用？
static string suffix = "abcdefghijklmnopqrstuvwxyz";
static string save_dir = SAVE_DIR;

mapping save_dbase;

int     transfer_user(string arg);
void    global_destruct_player(object ob, int raw);
void    transfer_autoload(object user, string card_file);
string *get_user_list(string dir);
object  global_find_player(string user);
mapping assure_user_file(string user, int flag);

void create()
{
        // 载入原来的 dbased 数据
        if (clonep() || ! this_player(1))
        {
                destruct(this_object());
                return;
        }

        seteuid(getuid());
        restore();

        set_name("用户档案导入器", ({ "data importer", "importer", }));
        set_weight(1);

        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "台");
                set("long", "这是一台用户档案导入器，请输入 help "
                            "importer 查看详细使用说明。\n");
        }
        setup();

        move(this_player(1));
}

void setup()
{
        ::setup();
}

mixed query_object_data(string index) { return save_dbase[index]; }
mapping query_save_dbase() { return save_dbase; }

string query_save_file() { return save_dir + "dbased"; }

void init()
{
        add_action("do_help", "help");
        add_action("do_batch", "batch");
        add_action("do_merge", "merge");
}

int do_help(string arg)
{
        switch (arg)
        {
        case "importer":
                write(@HELP
在这里你可以使用以下这些和用户档案导入器相关的命令：
    batch        批量导入用户数据。
HELP );
                break;

        case "batch":
                write(@HELP_BATCH
指令格式 : batch

批量导入用户数据。

相关指令：import, merge
HELP_BATCH );
                break;

        case "merge":
                write(@HELP_BATCH
指令格式 : merge dbase

将另外站点的数据库并入目前站点的数据库。

相关指令：batch
HELP_BATCH );
                break;

        default:
                return notify_fail("你要查看什么帮助？\n");
        }

        return 1;
}

// 获得一个不重复的用户名
mapping assure_user_file(string user, int flag)
{
#if 0
        int times;
        mapping file = ([ ]);

        for (times = 0; times < SUFFIX_SIZE; times++)
        {
                file["login_to"] = sprintf("%slogin/%c/%s%c.o", 
                                           DATA_DIR, user[0], 
                                           user, suffix[times]);

                file["user_to"] = sprintf("%suser/%c/%s%c.o", 
                                          DATA_DIR, user[0], 
                                          user, suffix[times]);

                file["uid"] = sprintf("%s%c", user, suffix[times]);

                if (file_size(file["login_to"]) < 0 ||
                    file_size(file["user_to"]) < 0)
                        return file;
        }
#else
        mapping file = ([ ]);

        file["login_to"] = sprintf("%slogin/%c/%s%s.o", 
                                   DATA_DIR, user[0], 
                                   user, "_" + SUFFIX_NAME);

        file["user_to"] = sprintf("%suser/%c/%s%s.o", 
                                  DATA_DIR, user[0], 
                                  user, "_" + SUFFIX_NAME);

        file["uid"] = sprintf("%s%s", user, "_" + SUFFIX_NAME);

        if (flag ||
            file_size(file["login_to"]) < 0 ||
            file_size(file["user_to"]) < 0)
                return file;

#endif
        return 0;
}

// 获得指定目录下所有的用户列表
string *get_user_list(string dir)
{
        string *sub_dir_list;
        string  sub_dir;
        string *user_list;
        string *temp_list;

        dir += "login/";

        sub_dir_list = get_dir(dir);
        sub_dir_list = filter_array(sub_dir_list, 
                                    (: file_size($(dir) + $1) == -2 :));
        sub_dir_list = map_array(sub_dir_list, (: $(dir) + $1 + "/" :));

        user_list = ({ });

        foreach (sub_dir in sub_dir_list)
        {
                temp_list = get_dir(sub_dir);

                if (! arrayp(temp_list) || ! sizeof(temp_list))
                        continue;

                reset_eval_cost();

                temp_list = filter_array(temp_list, (: sscanf($1, "%*s.bak") == 0 :));
                temp_list = map_array(temp_list, (: $1[0..<3] :));
                user_list += temp_list;
        }
        return user_list;
}

// 寻找或调入某一个玩家，本来可以使用 UPDATE_D 中的同名函数，
// 但因为这里直接析构了 login_ob，无法对 login_ob  做改名操
// 作。所以需要用到这个函数。

// 如果程序处理中需要更新那些不在线的玩家，则可以使用该函数
// 将这个玩家调入并且进行修改，请注意：修改完毕以后程序必须
// 保存玩家，并且使用 global_destruct_player 将玩家析构，如
// 果没有调用这个函数，则赋予玩家的定时器会自动析构玩家。
object global_find_player(string user)
{
        object ob;
        object login_ob;

        ob = find_player(user);
        if (! ob)
        {
                login_ob = new(LOGIN_OB);
                login_ob->set("id", user);
                ob = LOGIN_D->make_body(login_ob);
                if (! ob)
                {
                        catch(destruct(login_ob));
                        return 0;
                }

                evaluate(bind((: seteuid(getuid()) :), ob));

                if (! ob->restore())
                {
                        catch(destruct(login_ob));
                        catch(destruct(ob));
                        return 0;
                }

                ob->set_temp("temp_loaded", 1);
                ob->set_temp("link_ob", login_ob);

                ob->start_call_out(bind((: call_other, __FILE__, 
                                   "global_destruct_player", ob, 0 :),
                                   ob), 0);

                login_ob->restore();
                login_ob->set_temp("body_ob", ob);
        }

        return ob;
}

// 析构一个被 UPDATE_D 调入的玩家
void global_destruct_player(object ob, int raw)
{
        object login_ob;

        if (objectp(ob) && ob->query_temp("temp_loaded"))
        {
                // 增加对 login_ob 的析构
                if (objectp(login_ob = ob->query_temp("link_ob")))
                {
                        if (raw) login_ob->save();
                        destruct(login_ob);
                }
                
                if (raw) ob->save();
                destruct(ob);
        }
}

// 有哪些东西不可以继续允许 autoload 载入？

// 玩家自造的物品，考虑到玩家的 ID 可能改变了，
// 如果继续载入势必影响其他的玩家，所以必须删
// 除 autoload。 现在看来，似乎只有这一种，考
// 虑到这一种并不需要把文件载入就可以查出，所
// 以这里可以简单的通过 sscanf & filter_array
// 来处理用户的 autoload 列表， 过滤掉 /data/
// 目录下的文件。
void transfer_autoload(object user, string card_file)
{
        string *autoload;

        autoload = user->query_autoload_info();

        if (! arrayp(autoload) || ! sizeof(autoload))
                return;

        autoload = filter_array(autoload, 
                                (: (! sscanf($1, "/data/%*s")) :));
                                
        if (stringp(card_file))
                autoload += ({ card_file });

        user->set_autoload_info(autoload);
}

int do_merge(string arg)
{
        mapping m1, m2;
        string  mk;
        string  key, new_key, id, iname;
        object  ob;
        int     ok;

        if (arg != "dbase")
                return notify_fail("你要并入什么？\n");

        foreach (key in keys(save_dbase))
        {
                reset_eval_cost();

                if (sscanf(key, DATA_DIR "item/ring/%s", id))
                {
                        // Ring information
                        new_key = key + "_" + SUFFIX_NAME;
                } else
                if (sscanf(key, DATA_DIR "item/%*s/%s-%s", id, iname) == 3)
                {
                        // Item information
                        new_key = sprintf(DATA_DIR "item/%c/%s-%s",
                                          id[0], id + "_" + SUFFIX_NAME, iname);
                } else
                {
                        write("Ignore key - " + key + "!\n");
                        continue;
                }

                if (mapp(save_dbase[key]) && mapp(m1 = save_dbase[key]["owner"]))
                {
                    /* Convert data */
                    m2 = allocate_mapping(sizeof(m1));
                    foreach (mk in keys(m1))
                    {
                        m2[mk + "_" + SUFFIX_NAME] = m1[mk];
                    }
                    save_dbase[key]["owner"] = m2;
                }

                ok = DBASE_D->set_object_data(new_key, save_dbase[key]);
                if (! ok)
                {
                        write(HIR "Failed to set object information: " + new_key + "\n" NOR);
                        continue;
                }

                if (objectp(ob = find_object(new_key)))
                        ob->restore();
        }

        return 1;        
}

int do_batch()
{
        int i;
        string *user_list;
        string user;

        user_list = get_user_list(save_dir);

        write(WHT "开始迁移用户数据...\n\n" NOR);
        
        i = 0;
        foreach (user in user_list)
        {
                /* 开始转换的日志
                for (i = 1; i < LOG_LEVEL + 1; i++)
                        LOG(i, "Start transfering (" + user + ")'s data...\n");
                 */

                reset_eval_cost();

                if (transfer_user(user))
                {
                        i++;
                        write(sprintf("%-15s: Succeed\n", user));
                }
                else write(sprintf("%-15s: " WHT "Failed" NOR "\n", user));
        }
        
        write(WHT "\n迁移用户数据完成，共 " + sizeof(user_list) + 
              " 名用户，成功迁移 " + i + " 名用户。\n" NOR);
        return 1;
}

// 这两个定义是为了简化代码
#define user_file(x)    sprintf("%suser/%c/%s.o", save_dir, x[0], x)
#define login_file(x)   sprintf("%slogin/%c/%s.o", save_dir, x[0], x)

// 转换指定的用户
int transfer_user(string arg)
{
        object  user;
        object  link;
        object  card_ob;

        string  login_from;
        string  user_from;
        string  uid;
        string  card_file;
        string  couple_id;
        string  ring_file;

        string *item_list;
        string  item_name;
        string  item_file;
        string  file_content;

        mapping couple_file;
        mapping file;

        mixed   item_data;

        int     is_ok;

        // 找到旧的用户文件

        login_from = login_file(arg);
        user_from = user_file(arg);

        if (file_size(login_from) <= 0 || file_size(user_from) <= 0)
        {
                LOG(1, "File not found: (" + login_from + " & " + 
                        user_from + ").\n");
                return 0;
        }

        // 复制用户文件到 DATA_DIR

        file = assure_user_file(arg, 0);
        if (! file)
        {
                LOG(1, "User conflict: (" + login_from + " & " + 
                        user_from + ").\n");
                return 0;
        }

        if (! cp(login_from, file["login_to"]) || ! cp(user_from, file["user_to"]))
        {
                LOG(1, "Copy file to: (" + file["login_to"] + " | " + 
                       file["user_to"] + ") failed.\n");
                return 0;
        }

        uid = file["uid"];

        if (! objectp(user = global_find_player(uid)))
        {
                LOG(1, "Load user: (" + uid + ") failed.\n");
                return 0;
        }

        if (uid != arg)
        {
                // 修改 LOGIN_OB 和 USER_OB 的 ID
                if (objectp(link = user->query_temp("link_ob")))
                        link->set("id", uid);
        
                user->set("id", uid);
                LOG(2, "User ID (" + arg + ") changed into: (" + 
                        uid + ").\n");
        }

        // 添加姓名对应，中文姓名的雷同就算了吧。
        NAME_D->map_name(user->name(), uid);

        // 转换房屋为建房卡

        // 注意玩家手里的钥匙要收走，但是考虑到所有的
        // autoload 物品， 除了一些特殊情况外都要清除，
        // 所以这里暂不考虑。

        switch (user->query("private_room/type"))
        {
        case "盘龙居" : card_file = "/d/room/obj/ultracard"; break;
        case "彩虹居" : card_file = "/d/room/obj/super"; break;
        case "独乐居" : card_file = "/d/room/obj/card"; break;
        default : card_file = 0;
        }

        if (stringp(card_file))
        {
                user->delete("private_room");

                LOG(2, "Deleted (" + arg + ")'s private room.\n");
                LOG(3, "User (" + arg + ") get a free card.\n");
        }

        // 删除结义、同盟关系
        if (user->query("brothers"))
        {
                user->delete("brothers");
                LOG(2, "Deleted (" + arg + ")'s brother relation.\n");
        }

        if (user->query("league"))
        {
                user->delete("league");
                LOG(2, "Deleted (" + arg + ")'s league relation.\n");
        }

        // 删除帮派
        user->delete("party");

        // ...on 08/01 21:35.

        // 确认婚姻关系，考虑到配偶的 ID 有可能变化，
        // 所以这里要取得一个配偶唯一可能的 ID， 确
        // 保此用户的婚姻关系不出现问题，但问题在于，
        // 倘若在寻找这个配偶唯一可能的 ID 时，该配
        // 偶的文件已经转移到了 /data/ 下呢？就会弄
        // 糊涂了，因此，对于已经转移过的，要修改源
        // 目录内的文件名。
        couple_id = user->query("couple/id");
        
        if (stringp(couple_id))
        {
                // 改变配偶名字
                couple_file = assure_user_file(couple_id, 1);
                couple_id = couple_file["uid"];

                user->set("couple/id", couple_id);

                LOG(3, "User (" + arg + ")'s couple/id set to " + 
                       couple_id + ".\n");
                
                // 嗯，要自己保管好自己的结婚戒指
                if (user->query("can_summon/wedding ring"))
                {
                        ring_file = sprintf("%sitem/ring/%s.c", DATA_DIR, uid);

                        cp(sprintf("%sitem/ring/%s.c", save_dir, arg),
                           ring_file);

                        user->set("can_summon/wedding ring", 
                                  sprintf("%sitem/ring/%s.c", DATA_DIR, uid));

                        LOG(3, "User (" + arg + ")'s wedding ring copied to " + 
                               ring_file + ".\n");
                }

                // 从原来的数据中获得戒指的存盘信
                // 息，导入到 DBASE_D 中。
                ring_file = sprintf("%sitem/ring/%s", DATA_DIR, arg);
                item_data = query_object_data(ring_file);

                if (item_data)
                {
                        item_data["user"] = sprintf("%s(%s)", user->name(), uid);
                        is_ok = DBASE_D->set_object_data(sprintf("%sitem/ring/%s", 
                                                         DATA_DIR, uid), item_data);

                        LOG((is_ok ? 3 : 1), "Wedding ring data of (" + arg + 
                                             ") port to DBASE_D " + 
                                             (is_ok ? "succeed" : "failed") + ".\n");
                }
        }

        // 导入自造物品

        // 获得原来的自造物品列表
        item_list = get_dir(sprintf("%sitem/%c/%s-*.c", save_dir, arg[0], arg));

        if (arrayp(item_list) && sizeof(item_list))
        {
                foreach (item_name in item_list)
                {
                        // 要去掉后面的 .c 字样
                        item_file = sprintf("%sitem/%c/%s", DATA_DIR, arg[0], item_name[0..<3]);
                        item_data = query_object_data(item_file);

                        // 获得物品的具体名称
                        sscanf(item_name, arg + "-%s.c", item_name);
                        // 生成新的物品文件名
                        item_file = sprintf("%sitem/%c/%s-%s.c", DATA_DIR, uid[0], uid,
                                            item_name);
                        // 复制文件
                        is_ok = cp(sprintf("%sitem/%c/%s-%s.c", save_dir, arg[0], arg, item_name), 
                                   item_file);

                        if (! is_ok)
                        {
                                LOG(1, "Failed copy Item " + item_name + " of (" + arg + 
                                       ").\n");
                        } else
                        {
                                // 将文件中全部的原来的用户 ID
                                // 字样全部替换为新的
                                if (arg != uid)
                                {
                                        file_content = read_file(item_file);
                                        file_content = replace_string(file_content, arg, uid);
        
                                        write_file(item_file, file_content, 1);
                                }
        
                                if (item_data)
                                {
                                        // 修改 "user" 属性以适应新的 ID
                                        item_data["user"] = sprintf("%s(%s)", user->name(), uid);
        
                                        // 将原来的物品存盘信息导入 DBASE_D
                                        is_ok = DBASE_D->set_object_data(item_file, item_data);
                                }
        
                                // 更新用户身上的物品列表
                                user->set("can_summon/" + item_name, item_file);

                                LOG(3, "Item " + item_name + " of (" + arg + ") successfully "
                                       "tranfered.\n");
                        }
                }
        }
        // 转换用户的 autoload 信息，去掉无法继续
        // 使用的，如果获得了卡片，则增加卡片的载
        // 入信息
        transfer_autoload(user, card_file);

        // raw : 1，给 user 存一下盘
        global_destruct_player(user, 1);

        // 修改文件名，表示此用户已经转换
        rename(login_file(arg), login_file(arg) + ".bak");
        rename(user_file(arg), user_file(arg) + ".bak");

        LOG(3, "User (" + arg + ") successfully tranfered.\n");
        return 1;
}
