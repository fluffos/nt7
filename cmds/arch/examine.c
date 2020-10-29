// examine.c
// created by doing

#include <ansi.h>

inherit F_CLEAN_UP;

// 检查方式（手工检查则设置成为 EXAMINE_ALL）
#define        EXAMINE_ALL        0
#define        EXAMINE_LOGINED        1

protected string fname(object ob);
protected string examine_player(string name, int copy_user, int type, int last_touched);
protected string is_illegal(object ob, int update);

nosave int total_gold = 0;

void create() { seteuid(getuid()); }

public void search_dir(object me, int type);

int main(object me, string arg)
{
        int i;
        int copy_user;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg)
                return notify_fail("指令格式：examine [-u] <玩家ID> | -all\n");

        if (! sscanf(arg, "-u %s", arg))
                copy_user = 0;
        else
                copy_user = 1;

        if (arg != "-all")
        {
                string r;
                r = examine_player(arg, copy_user, EXAMINE_ALL, 0);
                if (! r) r = sprintf("这位玩家(%s)的数据没有异常。\n", arg);
                write("检查结果：" + r);
                return 1;
        }

        message_system("系统进行数据处理中，请耐心等候...\n");
        write(HIG "现在系统将检查所有玩家，稍后汇报。\n"
              HIG "进度：" + process_bar(0) + "\n");
        if (me)
        {
                me->attach_system();
                me->write_prompt();
        }
        search_dir(me, 0);
        return 1;
}

void search_dir(object me, int type)
{
        string *dir;
        string *result;
        string name;
        string info;
        mixed *ppls;
        int count;
        int total;
        int i;
        int j;

        if (! is_root(previous_object()))
                return 0;

        // Reset total gold counter
        total_gold =0;

        // Start examine all players
        log_file("examine", "SYSTEM start examine all player on " +
                 ctime(time()) + ".\n");
        dir = get_dir(DATA_DIR + "login/");
        result = ({ });
        count = 0;
        total = 0;
        for (i = 0; i < sizeof(dir); i++)
        {
                ppls = get_dir(DATA_DIR + "login/" + dir[i] + "/", -1);
                for (j = 0; j < sizeof(ppls); j++)
                {
                        reset_eval_cost();
                        if (sscanf(ppls[j][0], "%s.o", name) == 1)
                        {
                                info = examine_player(name, 0, type, ppls[j][2]);
                                if (! info) continue;
                                result += ({ info });
                                count++;
                        
                        }
                }
                total += j;
                message("system", ESC + "[1A" + ESC + "[256D"
                                  HIG "进度：" + process_bar((i + 1) * 100 / sizeof(dir)) +
                                  "\n" + (me ? HIR "执行中" NOR "> " : ""),
                                  me ? me : filter_array(all_interactive(), (: wizardp :)));
        }

        info = HIC "\n检查所有 " HIY + total +
               HIC " 玩家的结果如下：\n" NOR WHT;
        for (i = 0; i < sizeof(result); i++)
        {
                info += result[i];
                if (i % 20)
                {
                        log_file("examine", filter_color(info));
                        if (me) message("system", info, me);
                        info = "";
                }
        }

        if (! count)
                info += HIC "没有任何的玩家数据可能异样。\n" NOR;
        else
                info += HIG "共有 " + to_chinese(count) +
                        " 位玩家数据可能异常。\n\n" NOR;
        info += HIY "There are total " + total_gold + " golds.\n\n" NOR;

        log_file("examine", filter_color(info));

        if (me)
        {
                message("system", info, me);
                me->detach_system();
        }
}

protected string fname(object ob)
{
        string s1, s2;

        s1=query("surname", ob);
        s2=query("purename", ob);
        if (! s1) s1= "";
        if (s2) s1 += s2;
        if (s1 == "") s1 = "无名";
        return s1;
}

// Examine the player, if the player is illegal, I will return
// a detial string, or I will return 0
// If the flag copy_user has been set, I will login the user if
// he is offline
protected string examine_player(string name, int copy_user, int type, int last_touched)
{
        object me;
        object login_ob;
        object user_ob;
        string result;
        int day;
        int age;
        int online;
        mixed *st;
        int remove_flag;

        remove_flag = 0;
        if (type == EXAMINE_LOGINED)
        {
                if (! last_touched)
                {
                        st = stat(DATA_DIR + "login/" + name[0..0] + "/" +
                                  name + __SAVE_EXTENSION__);
        
                        if (! arrayp(st) || sizeof(st) < 3)
                                // 可能没有这个文件
                                return sprintf(WHT "无法查阅玩家(%s)的的登录信息。\n" NOR, name);
        
                        // 取最后访问 login_ob 的时间
                        last_touched = st[1];
                }

                // 计算没有上线的时间
                day = (time() - last_touched) / 86400;

                if (day >= 90 && ! objectp(find_player(name)))
                        //remove_flag = 1;
                        remove_flag = 0;
                else
                if (day >= 1)
                        // 这个文件最近没有访问过
                        return 0;
        }

        login_ob = new(LOGIN_OB);
        set("id", name, login_ob);

        if (! login_ob->restore())
        {
                destruct(login_ob);
                return sprintf(WHT "没有玩家(%s)。\n" NOR, name);
        }

        if( query("id", login_ob) != name )
        {
                string id;
                id=query("id", login_ob);
                destruct(login_ob);
                return sprintf(HIR "玩家(%s)的ID(%s)不正确。\n" NOR, name, id);
        }

        if (! objectp(user_ob = find_player(name)))
        {
                online = 0;
                user_ob = LOGIN_D->make_body(login_ob);
                if (! user_ob)
                {
                        destruct(login_ob);
                        return sprintf(HIR "无法生成玩家(%s)。\n" NOR, name);
                }

                if (! user_ob->restore())
                {
                        destruct(login_ob);
                        destruct(user_ob);
                        return sprintf(HIR "无法读取玩家档案(%s)。\n" NOR, name);
                }
        } else
                online = 1;

        if (remove_flag && ! online)
        {
                if( ultrap(user_ob) || query("immortal", user_ob) )
                {
                        // 永久保留的玩家：从新保存 login_ob，
                        // 刷新该人物的最后访问时间。
                        login_ob->save();
                        destruct(login_ob);
                        destruct(user_ob);
                        return 0;
                }

                // 删除该玩家
                destruct(login_ob);
                destruct(user_ob);
                log_file("static/purge",
                         sprintf("%s %s was purged by BACKUP_D\n",
                                 log_time(), name));
                UPDATE_D->remove_user(name);
                return 0;
        }

        result = is_illegal(user_ob, type == EXAMINE_LOGINED);
        if (result)
        {
                if (online)
                        result = sprintf("%s%-14s%-10s%s%-17s%s%s\n",
                                 WHT,
                                 name,
                                 query("name", user_ob),
                                 (interactive(user_ob) ? HIC : HIR),
                                 (interactive(user_ob) ? query_ip_number(user_ob) : "断线中"),
                                 NOR,
                                 result);
                else
                        result = sprintf("%s%-14s%-10s%s%-11s%-6s%s%s%s\n",
                                 WHT,
                                 name,
                                 query("name", user_ob),
                                 HIG,
                                 ctime(query("last_on", login_ob))[0..10],
                                 ctime(query("last_on", login_ob))[20..24],
                                 NOR,
                                 result,
                                 (user_ob->is_in_prison() ? HIR "(狱中)" NOR : ""));
        }

        destruct(login_ob);
        if (! online)
        {
                // the user is offline
                if (copy_user)
                {
                        me = this_player();
                        // I should login it
                        message_vision("$N口中念念有词，将$n变了出来。\n",
                                       me, user_ob);
                        catch(user_ob->setup());
                        catch(user_ob->restore_autoload());
                        catch(user_ob->move(environment(me)));
                } else
                {
                        // ok. logout the user
                        destruct(user_ob);
                }
        } else
        {
                if (copy_user)
                {
                        // login user? oh, I needn't do it because the
                        // user is online now.
                        write("玩家目前正在线上。\n");
                }
        }

        return result;
}

protected string is_illegal(object ob, int update)
{
        int gold;
        int age;
        int exp;
        int sp;
        int dt;
        int dexp, dpot, dmar, dage;
        mapping my, lex;

        if (wizhood(ob) != "(player)")
                return 0;

#if 0
        if( query("family/family_name", ob) != "华山派" && 
            ob->query_skill("hunyuan-zhang", 1))
                return "拥有混元掌技能";
#endif
        if( query_temp("user_setup", ob) )
                gold = MONEY_D->player_carry(ob);
        else
        {
                mapping list = ([
                        "/clone/money/thousand-cash"   : ({ 1000, 1, }),
                        "/clone/money/cash"   : ({ 10, 1, }),
                        "/clone/money/gold"   : ({ 1, 1, }),
                        "/clone/money/silver" : ({ 1, 100, }),
                        "/clone/money/coin"   : ({ 1, 10000, }),
                ]);

                int *val;
                string *autoload;
                string item;
                int amount;
                int i;

                // the user is load by another object but not logind,
                // or the user maybe failed to login, so I will check
                // the autoload of the user.
                autoload = ob->query_autoload_info();
                gold=query("balance", ob)/10000;

                if (autoload) i = sizeof(autoload); else i = 0;
                for (--i; i >= 0; i--)
                {
                        if (sscanf(autoload[i], "%s:%d", item, amount) != 2)
                                continue;

                        if (! arrayp(val = list[item])) continue;
                        gold += amount * val[0] / val[1];
                        if (gold < 0) break;    // Too much money
                }
        }

        // trans to gold
        my = ob->query_entire_dbase();
        lex = my["last_examine"];
        if (! mapp(lex))
                lex = ([ ]);

        if (! intp(my["mud_age"]) ||
            ! intp(my["combat_exp"]) ||
            ! intp(my["potential"]) ||
            ! intp(my["experience"]) ||
            ! intp(lex["mud_age"]) ||
            ! intp(lex["combat_exp"]) ||
            ! intp(lex["potential"]) ||
            ! intp(lex["experience"]) ||
            ! intp(lex["time"]))
                return HIR "数据类型错误" NOR;

        age = my["mud_age"] / 86400 / 6;
        exp = my["combat_exp"];
        dexp = exp - lex["combat_exp"];
        dpot = my["potential"] - lex["potential"];
        dmar = my["experience"] - lex["experience"];
        dage = my["mud_age"] - lex["mud_age"];
        dt = time() - lex["time"];
        lex = allocate_mapping(6);
        //if (dt > 60 && update)
        if (dt > 60)
        {
                lex["combat_exp"] = exp;
                lex["potential"] = my["potential"];
                lex["experience"] = my["experience"];
                lex["mud_age"] = my["mud_age"];
                lex["all_quest"] = my["all_quest"];
                lex["time"] = time();
                set("last_examine", lex, ob);
                if( !query_temp("user_setup", ob) )
                        ob->save();
        }

        total_gold += gold;

        if (gold > 20000)
                return HIY "拥有 " + gold + " 两黄金" NOR;

        if (exp < 1000000 && gold >= 10000)
                return HIC "经验 1M 以内拥有 " + gold + " 两黄金" NOR;

        if (exp > 10000 && dt > 60)
        {
                if ((sp = dexp * 60 / dt) > 9000)
                        return HIR "平均经验速度太快(" + sp + "/分钟:" + dt / 60 + "分钟)" NOR;

                if ((sp = dpot * 60 / dt) > 2000)
                        return HIR "平均潜能速度太快(" + sp + "/分钟:" + dt / 60 + "分钟)" NOR;

                if ((sp = dmar * 60 / dt) > 1000)
                        return HIR "平均体会速度太快(" + sp + "/分钟:" + dt / 60 + "分钟)" NOR;

                if (dage > dt + 60)
                        return HIR "连线时间超过系统间隔时间(" + ((dage - dt) / 60) + "分钟)。" NOR;
        }

        if (gold >= 10000 && age < 1)
                return HIC "14岁拥有 " + gold + " 两黄金" NOR;

        return 0;
}

int  help(object  me)
{
write(@HELP
指令格式：examine [-u] <玩家ID> | -all

查找玩家，判断数据是否正常。如果使用了[-u]参数，则除了检查玩
家，还会将不在线上玩家复制出来，以供详细查阅。

判断依据：
1. 超过 20000 两黄金。
2. 经验 1M 以内超过 3000 两黄金。
3. 平均经验速度超过 (90/m)。
4. 平均潜能速度超过 (20/m)。
5. 平均体会速度超过 (10/m)。
6. 14岁金钱超过 100 两黄金。

HELP
    );
        return  1;
}
