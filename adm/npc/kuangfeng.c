// kuangfeng.c

#include <ansi.h>
inherit NPC;

#define WARCRAFT_OB             "/clone/npc/warcraft.c"
#define WARCRAFT_DIR            "/data/warcraft/"
#define CRUISE_OB               "/clone/misc/qiankun_ob.c"
#define BELT_OB                 "/clone/misc/belt_ob.c"

void get_subtype(string arg, object ob);
void get_gender(string arg, object ob);
void get_id(string arg, object ob);
void get_name(string arg, object ob);
void get_desc(string arg, object ob);
void build_warcraft(object ob);
int check_legal_name(string name, int max_len);
int check_legal_id(string arg);

string* warcraft_type = ({
        "青龙",
        "白虎",
        "朱雀",
        "玄武",
        "麒麟",
});

mapping magic_type = ([ 
        "青龙" : "wood",
        "白虎" : "metal",
        "朱雀" : "fire",
        "玄武" : "water",
        "麒麟" : "earth",
]);

void create()
{
        set_name("狂风", ({ "kuang feng", "kuang", "feng" }) );
        set("gender", "男性" );
        set("age", 21);
        set("long",@LONG
狂风来自神秘的精意山庄，最近突然出现在扬州城，并出售
人们从没有见过的魔幻兽，传说这个魔幻兽具有神奇的功能，
你如果喜欢的话，不妨也选(choose)一只。
LONG );
        set("title",HIW"炼器师"NOR);
        set("combat_exp", 5000000);

        set("inquiry", ([
                "魔幻兽"     : "只要给我一张魔幻兽兑换券，你就能拥有魔幻兽了！",
                "如意乾坤袋" : "给我材料地藏之石，你就可以拥有如意乾坤袋了。",
                "乾坤袋"     : "给我材料地藏之石，你就可以拥有如意乾坤袋了。",
                "勋章挂带"   : "给我材料魔法丝带，你就可以拥有勋章挂带了。",
        ]));

        set_skill("training", 100000);

        set_skill("huisheng-jue", 100000);
        set("chat_chance", 15);
        set("attitude", "friendly");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        create_family("精意山庄", 2, "弟子");
}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_choose", "choose");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(5) ) {
                case 0:
                        say( "狂风说道：这位" + RANK_D->query_respect(ob)
                                + "，要魔幻兽么？\n");
                        break;
                case 1:
                        say( "狂风说道：这位" + RANK_D->query_respect(ob)
                                + "，魔幻兽可以保护主人的哦。\n");
                        break;
        }
}

int do_choose()
{
        object warcraft;
        string filename;
        object me = this_player();

        if (me->is_busy())
                return notify_fail("你上一个动作还没有完成。\n");

        filename = WARCRAFT_DIR+query("id", me);
        if (file_size(WARCRAFT_DIR+query("id", me)+FILE_EXTENSION) > 0)
        {
                catch(call_other(filename, "???"));
                warcraft = find_object(filename);
                set("can_whistle/"+query("id", warcraft), filename, me);
                set("warcraft/id", query("id", warcraft), me);
                set("warcraft/file", filename, me);
                set("warcraft/status", "living", me);
                MYGIFT_D->check_mygift(me, "newbie_mygift/warcraft"); 
                return notify_fail("你宿命中已经拥有过魔幻兽，我已经帮你沟通血契了。\n");
        }

        if (me->query_skill("training", 1) <30)
                return notify_fail("你的驭兽术太低了，即使养了魔幻兽，也会背弃你而去。\n");

        if( !query_temp("warcraft/money", me) )
        {
                command("say 这位" + RANK_D->query_respect(me) + "，每只魔幻兽一百两黄金，你必须先给钱！");
                return 1;
        }

        write("您要养哪类魔幻兽：\n");
        write(" 1. 青龙   2. 白虎   3. 朱雀   4. 玄武  5. 麒麟\n");
        write("请选择数字代号：(q 键取消)");

        input_to( (: get_subtype :), me);
        return 1;
}

void get_subtype(string arg, object ob)
{
        int n;

        if (arg == "q" || arg == "Q")
                return;

        sscanf(arg, "%d", n);

        if (n <= 0 || n > 5)
        {
                write("您要养哪类魔幻兽：\n");
                write(" 1. 青龙   2. 白虎   3. 朱雀   4. 玄武  5. 麒麟\n");
                write("请选择数字代号：(q 键取消)");
                input_to( (: get_subtype :), ob);
                return;
        }
        set_temp("warcraft/race_type", warcraft_type[n-1], ob);

        write("\n");
        write("请设定魔幻兽的性别(雄性：1  雌性：0)：");
        input_to( (: get_gender :), ob );
}

void get_gender(string arg, object ob)
{
        int n;
        object warcraft;

        sscanf(arg, "%d", n);

        if (n != 0 && n != 1)
        {
                write("\n");
                write("请设定魔幻兽的性别(雄性：1  雌性：0)：");
                input_to( (: get_gender :), ob );
                return;
        }
        set_temp("warcraft/gender", n?"男性":"女性", ob);

        write("\n");

        write(sort_string(CYN "你按照狂风的指点开始飞快的念道：“在天的见"
                "证之下，集勇气、智慧、与美丽于一身的强大生物，幻兽呀！请"
                "你以最深的灵性，聆听我的倾诉，我－"+query("name", ob)+
                "－将与你缔结永生的血之盟约，终此生惟有你与我为终生之盟友"
                "，契。”\n" NOR, 64));
        write("你与魔幻兽的血之盟约签订完毕。\n");
        write("请设定魔幻兽的英文 id ：");
        input_to( (: get_id :), ob );
}

void get_id(string arg, object ob)
{
        arg = lower_case(arg);

        if (! check_legal_id(arg))
        {
                write("\n");

                write("请设定魔幻兽的英文 id ：");
                input_to( (: get_id :), ob );
                return;
        }

        arg = replace_string(arg, " ", "_");

        set_temp("warcraft/id", arg, ob);

        write("\n");
        write("请设定魔幻兽的中文名：(可加颜色help nick)");
        input_to( (: get_name :), ob);
}

void get_name(string arg, object ob)
{
        string  arg_old;
        string  result;

        if( arg && query_temp("big5", ob) )
                arg = LANGUAGE_D->toGB(arg);

        arg_old = arg;

        arg = trans_color(arg, 3);
        arg = filter_color(arg);

        if (! check_legal_name(arg, 12))
        {
                write("请设定魔幻兽的中文名：(可加颜色)");
                input_to( (: get_name :), ob);
                return;
        }

        if (stringp(result = NAME_D->invalid_new_name(arg)))
        if (stringp(result = NAME_D->invalid_new_name(arg)) || strsrch(arg, "张春龙") != -1)
        {
                write("对不起，" + result);
                write(HIR "禁止使用与他人姓名相同或接近的魔幻兽名。并因循RULES中对名字的相关规定。"NOR+"\n");
                input_to( (: get_name :), ob);
                return;
        }

        arg = arg_old;
        arg = trans_color(arg, 3);

        set_temp("warcraft/name", arg, ob);

        write("\n");
        write("请描述魔幻兽：(不可加颜色)");
        input_to( (: get_desc :), ob);
}

void get_desc(string arg, object ob)
{
        if( arg && query_temp("big5", ob) )
                arg = LANGUAGE_D->toGB(arg);

        arg = replace_string(arg, "\"", "");
        arg = replace_string(arg, "\\", "");
        if (! check_legal_name(arg, 60))
        {
                write("请描述魔幻兽：");
                input_to( (: get_desc :), ob);
                return;
        }

        set_temp("warcraft/desc", arg, ob);
        write("ok\n");
        build_warcraft(ob);
}

void build_warcraft(object ob)
{
        string file, filename;
        object warcraft, money;
        string warcraft_id;
        string warcraft_name;
        string warcraft_type;
        string warcraft_desc;
        string warcraft_gender;

        warcraft_id=query_temp("warcraft/id", ob);
        warcraft_name=query_temp("warcraft/name", ob);
        warcraft_name += NOR;

        warcraft_desc=query_temp("warcraft/desc", ob);
        warcraft_desc += NOR;
        warcraft_gender=query_temp("warcraft/gender", ob);
        warcraft_type = query_temp("warcraft/race_type", ob);

        file = read_file(WARCRAFT_OB);

        file = replace_string(file, "WARCRAFT_NAME", warcraft_name);
        file = replace_string(file, "WARCRAFT_ID", warcraft_id);
        file = replace_string(file, "WARCRAFT_GENDER", warcraft_gender);
        file = replace_string(file, "RACE_TYPE", warcraft_type);
        file = replace_string(file, "MAGIC_TYPE", magic_type[warcraft_type]);
        file = replace_string(file, "LONG_DESCRIPTION",
                            warcraft_desc + "\n" + "它是" +
                            query("name", ob)+"的魔幻兽。\n");

        file=replace_string(file,"OWNER_ID",query("id", ob));
        file=replace_string(file,"OWNER_NAME",query("name", ob));

        filename=WARCRAFT_DIR+query("id", ob);
        if (file_size(filename + ".c") > 0)
        {
                if (warcraft = find_object(filename))
                        destruct(warcraft);
                DBASE_D->clear_object(filename);
                rm(filename + ".c");
        }

        assure_file(filename);
        write_file(filename + ".c", file); // 写入文件
        VERSION_D->append_sn(filename + ".c"); // 给物品增加识别码

        catch(call_other(filename, "???"));
        warcraft = find_object(filename);
        if (! warcraft)
        {
                delete_temp("warcraft", ob);
                money = new("/clone/money/gold");
                money->set_amount(100);
                money->move(ob, 1);
                message_vision("$N一呆，对$n道：抱歉抱歉！出了一些问题！钱我还是还你吧。\n",
                               this_object(), ob);
                return;
        }
        set("level", 1, warcraft);

#ifdef DB_SAVE
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();
        DATABASE_D->db_remove_item(filename);
        DATABASE_D->db_create_item(warcraft, warcraft->query_entire_dbase());
#endif
        warcraft->save();
        destruct(warcraft);

        set("can_whistle/"+warcraft_id, filename, ob);
        set("warcraft/id", warcraft_id, ob);
        set("warcraft/file", filename, ob);
        set("warcraft/status", "living", ob);
        delete_temp("warcraft", ob);

        command("say 你可以吹声口哨召唤你的魔幻兽！<whistle " + warcraft_id +">\n");

        MYGIFT_D->check_mygift(ob, "newbie_mygift/warcraft");   
        return;
}

int accept_object(object me, object ob)
{
        string filename;
        string file;
        object cruise_ob, xob;

        if( query("id", ob) == "dizang zhishi" )
        {
                filename=ITEM_DIR+"cruise/"+query("id", me);
                if (file_size(filename + ".c") > 0)
                {
                        message_vision("$N一呆，对$n道：你的宿命中已经拥有过如意乾坤袋！我帮你恢复了。\n",
                                       this_object(), me);
                        set("can_summon/qiankun", filename, me);
                        return 0;
                }

                command("say 这可是制作如意乾坤袋的特殊材料，既然你我有缘，我就免费帮你制作一个吧！");
                if (1)
                {
                        file = read_file(CRUISE_OB);
                        file = replace_string(file, "LONG_DESCRIPTION",
                                                "这是" + me->query_idname(1) + "的如意乾坤袋。\n");

                        // give cruise ob to me
                        filename=ITEM_DIR+"cruise/"+query("id", me);
                        if (file_size(filename + ".c") > 0)
                        {
                                if (cruise_ob = find_object(filename))
                                        destruct(cruise_ob);

                                DBASE_D->clear_object(filename);
                                rm(filename + ".c");
                                //log_file("cruise_ob",sprintf("%s have new cruise ob.\n",query("id", me)));
                        }
                        assure_file(filename);
                        write_file(filename + ".c", file);
                        VERSION_D->append_sn(filename + ".c");

                        catch(call_other(filename, "???"));
                        cruise_ob = find_object(filename);
                        if (! cruise_ob)
                        {
/*
                                xob = new("/clone/item/dizangshi");
                                xob->move(me, 1);
*/
                                message_vision("$N一呆，对$n道：抱歉抱歉！出了一些问题！材料我还是还你吧。\n",
                                               this_object(), me);
                                return 0;
                        }
#ifdef DB_SAVE
                        if (! DATABASE_D->query_db_status())
                                DATABASE_D->connect_to_database();
                        DATABASE_D->db_remove_item(filename);
                        DATABASE_D->db_create_item(cruise_ob, cruise_ob->query_entire_dbase());
#endif

                        cruise_ob->move(me, 1);
                        cruise_ob->save();
                        set("can_summon/qiankun", filename, me);

                        tell_object(me, HIY "你获得了一个如意乾坤袋。\n" NOR);
                        tell_object(me, HIY "你可以通过summon qiankun和hide qiankun来召唤和隐藏如意乾坤袋。\n" NOR);
                        destruct(ob);
                        return 1;
                }
        }

        if( query("id", ob) == "magic silk" )
        {
                filename=ITEM_DIR+"belt/"+query("id", me);
                if (file_size(filename + ".c") > 0)
                {
                        message_vision("$N一呆，对$n道：你的宿命中已经拥有过勋章挂带！我帮你恢复了。\n",
                                       this_object(), me);
                        set("can_summon/belt", filename, me);
                        return 0;
                }

                command("say 这可是制作勋章挂带的特殊材料，既然你我有缘，我就免费帮你制作一个吧！");
                if (1)
                {
                        file = read_file(BELT_OB);
                        file = replace_string(file, "LONG_DESCRIPTION",
                                                "这是" + me->query_idname(1) + "的勋章挂带。\n");

                        // give cruise ob to me
                        filename=ITEM_DIR+"belt/"+query("id", me);
                        if (file_size(filename + ".c") > 0)
                        {
                                if (cruise_ob = find_object(filename))
                                        destruct(cruise_ob);

                                DBASE_D->clear_object(filename);
                                rm(filename + ".c");
                                //log_file("cruise_ob",sprintf("%s have new cruise ob.\n",query("id", me)));
                        }
                        assure_file(filename);
                        write_file(filename + ".c", file);
                        VERSION_D->append_sn(filename + ".c");

                        catch(call_other(filename, "???"));
                        cruise_ob = find_object(filename);
                        if (! cruise_ob)
                        {
                                message_vision("$N一呆，对$n道：抱歉抱歉！出了一些问题！材料我还是还你吧。\n",
                                               this_object(), me);
                                return 0;
                        }
#ifdef DB_SAVE
                        if (! DATABASE_D->query_db_status())
                                DATABASE_D->connect_to_database();
                        DATABASE_D->db_remove_item(filename);
                        DATABASE_D->db_create_item(cruise_ob, cruise_ob->query_entire_dbase());
#endif

                        cruise_ob->move(me, 1);
                        cruise_ob->save();
                        set("can_summon/belt", filename, me);

                        tell_object(me, HIY "你获得了一个勋章挂带。\n" NOR);
                        tell_object(me, HIY "你可以通过summon belt和hide belt来召唤和隐藏勋章挂带。\n" NOR);
                        destruct(ob);
                        return 1;
                }
        }
        if( query("id", ob) == "duihuan juan" )
        {
                if (me->query_skill("training", 1) < 30)
                {
                        command("say 你的驭兽术不够，即使养了魔幻兽，也会离你而去！");
                        return 0;
                }
                else
                {
                        set_temp("warcraft/money", 1, me);
                        command("say 好我收下了！");
                        command("say " + me->name() +
                                     "，现在我这里有各种魔幻兽！");
                        command("say 请选择你要的魔幻兽 < choose >");
                        destruct(ob);
                        return 1;
                }
        }
        return 0;
}

int check_legal_id(string id)
{
        int i;
        string *legalid;
        object ppl;

        i = strlen(id);

        if ((strlen(id) < 3) || (strlen(id) > 20))
        {
                write("对不起，英文 id 必须是 3 到 20 个英文字母。\n");
                return 0;
        }

        while(i--)

        if (id[i] != ' ' && (id[i] < 'a' || id[i] > 'z'))
        {
                write("对不起，英文 id 只能用英文字母。\n");
                return 0;
        }

        ppl = LOGIN_D->find_body(id);

        if (ppl || id == "guest" || id == "new")
        {
                write("这个名字与别的玩家ID相同了．．．");
                return 0;
        }

        if (file_size(sprintf("/data/user/%c/%s", id[0], id)
                    + __SAVE_EXTENSION__) >= 0)
        {
                write("这个名字已经被别的玩家使用了．．．");
                return 0;
        }

        return 1;
}

int check_legal_name(string name, int max_len)
{
        int i;
        string  *legalname;             //not implemented..may add later

        i = strlen(name);
        if ((strlen(name) < 2) || (strlen(name) > max_len ))
        {
                write(sprintf("对不起，魔幻兽中文字必须是 1 到 %d 个中文字。\n",
                      max_len / 2));
                return 0;
        }

        if (max_len < 13 && ! is_chinese(name))
        {
                write("对不起，请您用「中文」为宠物取名字或描述。\n");
                return 0;
        }
        return 1;
}

int attempt_apprentice(object ob)
{
        command("say 滚！给我一边儿去！");
}

int recognize_apprentice(object me, string skill)
{
        if (skill == "training" || skill == "huisheng-jue")
                return 1;
        else
                return 0;
}
