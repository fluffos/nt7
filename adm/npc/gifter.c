// This program is a part of NT MudLIB

#include <ansi.h>

inherit NPC;

int get_reward();
mixed ask_gift();
mixed ask_gift1();
mixed ask_gift2();
mixed ask_gift3();
mixed ask_gift4();
mixed ask_gift5();
mixed ask_gift6();

void create()
{
        set_name(HIM "礼物天使" NOR, ({ "gift angel", "tianshi", "gift", "angel", "liwu" }));
        set("long", @LONG
礼物天使，负责泥潭节庆期间礼物发放的天使。
LONG);
        set("gender", "女性" );
        set("age", 18);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 1200000);

        set("inquiry", ([
                "节日礼物" : (: get_reward :),
                "礼物" : (: get_reward :),
/*
                "gift" : (: ask_gift :),
                // "国庆礼物" : (: ask_gift1 :),
                // "会员体验" : (: ask_gift2 :),
                // "元旦礼物" : (: ask_gift3 :),
                "春节礼物" : (: ask_gift4 :),
                // "春节特殊礼物" : (: ask_gift5 :),
                // "新人福利" : (: ask_gift6 :),
*/
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

}

int get_reward()
{
        object me;
        string ret;

        me = this_player();
        ret = FESTIVAL_D->get_reward(me);
        tell_object(me, ret);
        return 1;
}

mixed ask_gift()
{
        object ob, me = this_player();
        string *lines;
        string file, gift;
        int time1, time2;

        file = read_file(CONFIG_DIR + "gift");
        if (! stringp(file))
        {
                command("say 可惜，天神还没有打算做任务礼物呢！");
                return 1;
        }

        lines = explode(file, "\n");
        file = lines[sizeof(lines) -1];

        if (sscanf(file, "%s %d to %d", gift, time1, time2) != 3)
        {
                command("say 奇怪，礼物怎么不见了，难道是天神在作怪？！");
                return 1;
        }

        if( query("gifter/"+time1, me) )
        {
                command("say 呵呵～这就是您的不是了！我已经给过您礼物了啊！");
                return 1;
        }

        if (time() < time1 || time() > time2)
        {
                command("say 对不起，你来的不是时候，现在送你礼物，天神会惩罚我的！");
                return 1;
        }

        if (! ob = new(gift))
        {
                 command("say 奇怪，礼物有大问题，你赶快和天神报告吧！");
                 return 1;
        } else
        {
                set("gifter/"+time1, 1, me);
                ob->move(me, 1);

                message_vision(HIW "$N" HIW "凌空一指，突然天空中一道" HIM "七" HIY "彩" HIR "霞" HIC "光" HIW "笼罩$n，转瞬即逝！\n" NOR,
                               this_object(), me);

                tell_object(me, HIG "你身上好象多了一个礼物（gift），你快看看是什么礼物吧。\n" NOR);
                return 1;
        }
}

mixed ask_gift1()
{
        int td;
        object ob;
        object me = this_player();

        td = time() / 86400;

        if( query("gifter/which_day", me) == td )
                return "你今天已经领过礼物了。";

        tell_object(me, HIY "\n你领取了一个今天的礼物(" HIM "天师护身符" NOR + HIY ")，祝你在王者归来里玩的愉快！\n" NOR);

        ob = new("/clone/goods/tianshi-charm");
        ob->move(me, 1);
        set("bindable", 3, ob);
        set("bind_owner",query("id",  me), ob);
        set("autoload", 1, ob);
        set("setdbase", 1, ob);
        set("gifter/which_day", td, me);
        return 1;
}

mixed ask_gift2()
{
        string id, sql;
        int    jointime, endtime, day;
        object me = this_player();


        if( query("gifter/monfee1", me) )
                return "你已经体验过会员了。";

        id=query("id", me);

        if (! MEMBER_D->is_member(id))
        {
                day = time() + 2678400;
                sql = sprintf("INSERT INTO %s SET id = \"%s\", jointime = %d, endtime = %d",
                              "members", id, time(), day);
                DATABASE_D->db_query(sql);
        } else
        {
                jointime = (int)MEMBER_D->db_query_member(id, "jointime");
                if (jointime < 1) jointime = time();

                endtime  = (int)MEMBER_D->db_query_member(id, "endtime");
                if (endtime < 1) day = time() + 2678400;
                else day = endtime + 2678400;

                sql = sprintf("UPDATE %s SET jointime = %d, endtime = %d WHERE id = \"%s\"",
                              "members", jointime, day, id);

                DATABASE_D->db_query(sql);
        }

        set("gifter/monfee1", 1, me);

        tell_object(me, HIY "\n你领取了一个月的(" HIM "会员体验" NOR + HIY ")，祝你在王者归来里玩的愉快！\n" NOR);

        return 1;
}

mixed ask_gift3()
{
        object me = this_player();


        if( query("gifter/20081224", me) )
                return "你已经领过元旦礼物了，不要太贪心。:)";

        if (! MEMBER_D->is_valid_member(me))
        {
                addn("combat_exp", 2000000, me);
                addn("potential", 3000000, me);
                addn("experience", 8000000, me);
                addn("time_reward/quest", 86400, me);
        } else
        {
                addn("combat_exp", 10000000, me);
                addn("potential", 6000000, me);
                addn("experience", 3000000, me);
                addn("balance", 500000000, me);
                addn("time_reward/quest", 172800, me);
        }

        set("gifter/20081224", 1, me);

        tell_object(me, HIY "\n天空突现一道金光照耀着你，你冥冥中感觉到在2009年将万事有如神助！\n" NOR);

        return 1;
}

mixed ask_gift4()
{
        string mapsk;
        object me = this_player();


        if( query("gifter/20120120", me) )
                return "你已经领过春节礼物了，不要太贪心。:)";

        addn("combat_exp", 2000000, me);
        addn("potential", 1000000, me);

        if (MEMBER_D->is_valid_member(me))
        {
                mapsk = me->query_skill_mapped("force");
                        me->improve_skill("force", 200000);
                        me->improve_skill("force", 200000);
                        me->improve_skill("force", 200000);
                        me->improve_skill("force", 200000);
                if (stringp(mapsk))
                {
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                }

                mapsk = me->query_skill_mapped("parry");
                        me->improve_skill("parry", 200000);
                        me->improve_skill("parry", 200000);
                        me->improve_skill("parry", 200000);
                        me->improve_skill("parry", 200000);
                if (stringp(mapsk))
                {
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                }

                mapsk = me->query_skill_mapped("dodge");
                        me->improve_skill("dodge", 200000);
                        me->improve_skill("dodge", 200000);
                        me->improve_skill("dodge", 200000);
                        me->improve_skill("dodge", 200000);
                if (stringp(mapsk))
                {
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                }

                addn("balance", 20000000000, me);
        }

        set("gifter/20120120", 1, me);

                tell_object(me,
HIW"\n"+
"     ┏---------------- "HIR"春节快乐"HIW" ----------------┓\n"+
"     ┃  ┌-------- Happy  New  Year --------┐  ┃\n"+
"     ┃  │                                  │  ┃\n"+
"     ┃  │                                  │  ┃\n");
                if( strlen(query("name", me)) == 2)tell_object(me,
HIW"┃│亲爱的"+query("name", me)+"：│┃\n");
                if( strlen(query("name", me)) == 4)tell_object(me,
HIW"┃│亲爱的"+query("name", me)+"：│┃\n");
                if( strlen(query("name", me)) == 6)tell_object(me,
HIW"┃│亲爱的"+query("name", me)+"：│┃\n");
                if( strlen(query("name", me)) == 8)tell_object(me,
HIW"┃│亲爱的"+query("name", me)+"：│┃\n");
                if( strlen(query("name", me)) == 10)tell_object(me,
HIW"┃│亲爱的"+query("name", me)+"：│┃\n");
        tell_object(me,
HIW"     ┃  │      愿您和您的家人在新的一年    │  ┃\n"+
"     ┃  │  里，健康、快乐、平安！          │  ┃\n"+
"     ┃  │                                  │  ┃\n"+
"     ┃  │             *  *"HIR"r"HIW"*  *            │  ┃\n"+
"     ┃  │          * *"HIR"a"HIW"* "HIG"^"HIY"Y"HIG"^"HIW" *"HIR"i"HIW"* *         │  ┃\n"+
"     ┃  │         *"HIM"m"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"*"HIG"^\\^"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"*"RED"s"HIW"*        │  ┃\n"+
"     ┃  │         "HIG"^"HIY"Y"HIG"^"HIW"*"HIG"\\"HIW"*"RED"e"HIW"*"HIG"/"HIW"*"HIG"l"HIW"*"HIG"/"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"        │  ┃\n"+
"     ┃  │         *"HIG"\\"HIW"*"CYN"t"HIW"*"HIG"|"HIY"Y"HIG"^\\^"HIY"Y"HIG"|"HIW"*"HIG"l"HIW"*"HIG"/"HIW"*        │  ┃\n"+
"     ┃  │        *"MAG"s"HIW"*"HIG"|"HIY"Y"HIG"^\\\\^/^//^"HIY"Y"HIG"|"HIW"*"HIR"a"HIW"*       │  ┃\n"+
"     ┃  │        "GRN"^"YEL"Y"GRN"^\\\\_^\\\\\\//^_//^"YEL"Y"GRN"^"HIW"       │  ┃\n"+
"     ┃  │        "GRN"^\\_^\\_\\_\\//_/_/^_/^"HIW"       │  ┃\n"+
"     ┃  │         "GRN"^^\\_^\\_\\\\/_/^_/^^"HIW"        │  ┃\n"+
"     ┃  │           "GRN"^^\\_ \\// _/^^"HIW"          │  ┃\n"+
"     ┃  │               "GRN"\\_\\_/"HIW"              │  ┃\n"+
"     ┃  │                "GRN"/|\\"HIW"               │  ┃\n"+
"     ┃  │               "GRN"/\\\\/\\"HIW"              │  ┃\n"+
"     ┃  │                                  │  ┃\n"+
"     ┃  │                  "RED"泥潭巫师组恭贺"HIW"  │  ┃\n"+
HIW"     ┃  └----------------------------------┘  ┃\n"+
"     ┗------------------------------------------┛\n"+
"\n" NOR);

        return 1;
}

mixed ask_gift5()
{
        object me = this_player();

        if( query("gifter/20090121", me) )
                return "你已经领过春节特殊礼物了，不要太贪心。:)";

        if (! MEMBER_D->is_valid_member(me))
                addn("time_reward/quest", 259200, me);
        else
                addn("time_reward/quest", 518400, me);

        set("gifter/20090121", 1, me);
        tell_object(me, HIY "\n你领取了春节特殊礼物，祝你新年快乐！\n" NOR);

        return 1;
}

mixed ask_gift6()
{
        object me = this_player();
        if( query("gifter/20090701", me) )
                return "你已经领过新人福利了，不要太贪心。:)";

        addn("max_neili", 100000, me);
        addn("max_jingli", 100000, me);
        set("gifter/20090701", 1, me);
        tell_object(me, HIY "\n你领取了新人福利，祝你玩得愉快！\n" NOR);
        return 1;
}
