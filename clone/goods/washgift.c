// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ITEM;

string *valid_types = ({
        "sword",
        "blade",
        "staff",
        "hammer",
        "club",
        "whip",
        "throwing",
});

int do_washto(string arg);

void create()
{
        set_name(HIR "洗天赋丹" NOR, ({"wash gift", "gift"}));
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "颗");
                set("long", @LONG
这是提供给那些出生时候选错天赋的人一次重新分配先天天赋的洗天赋丹。
洗天赋丹每人只能使用一次，格式为 washto <膂力> <悟性> <根骨> <身法>
例如：washto 20 20 20 20 ，洗天赋时候要求解完所有加先天的迷及吃全所
有加先天的丹和使用完mygift礼物的四点先天。
LONG );
                set("value", 1);
                set("no_sell", 1);
        }
        setup();
}

void init()
{
        object me = this_player();

        if (me == environment())
                add_action("do_washto", "washto");
}


int do_washto(string arg)
{
        int i, j, points;
        int tmpstr, tmpint, tmpcon, tmpdex;
        int str, wux, con, dex;
        object me, weapon;
        mapping my;
        string *sname;
        mixed skill_status;

        me = this_player();

        if (! arg || sscanf(arg, "%d %d %d %d", tmpstr, tmpint, tmpcon, tmpdex) != 4)
                return notify_fail("指令格式：washto <膂力> <悟性> <根骨> <身法>\n" +
                                   "例    如：washto 20 20 20 20\n");

        /*
        if( query("age", me) > 20 )
                return notify_fail("你已经过了新手期，在转世前不在拥有调整天赋的机会。\n");

        if (query("reborn/times", me))
                return notify_fail("洗天赋丹只能没有转世的玩家使用，你现在已经错过机缘了。\n");
        */

        if( query("gift/washed", me) >= 3 )
                return notify_fail("你已经使用洗天赋丹超过三次了，每人只有三次机会。\n");

        //if (tmpstr > 43 || tmpstr < 21)
        if (tmpstr > 100 || tmpstr < 13)
                return notify_fail("你所选择的膂力数值要求必须在21和43之间。\n");

        //if (tmpint > 43 || tmpint < 21)
        if (tmpint > 100 || tmpint < 13)
                return notify_fail("你所选择的悟性数值要求必须在21和43之间。\n");

        //if (tmpcon > 46 || tmpcon < 24)
        if (tmpcon > 100 || tmpcon < 13)
                return notify_fail("你所选择的根骨数值要求必须在24和46之间。\n");

        //if (tmpdex > 43 || tmpdex < 21)
        if (tmpdex > 100 || tmpdex < 13)
                return notify_fail("你所选择的身法数值要求必须在21和43之间。\n");

        my = me->query_entire_dbase();
        str = copy(my["str"]);
        wux = copy(my["int"]);
        con = copy(my["con"]);
        dex = copy(my["dex"]);

        points = str + wux + con + dex;
        if (tmpstr + tmpint + tmpcon + tmpdex != points)
                return notify_fail("你所重新选择的天赋数值和自己天赋的" + points + "总值不一致。\n");
        /*

        write(HIW "开始检查现有天赋下所学技能是否满足升级条件...\n" NOR);

        skill_status = me->query_skills();
        if (mapp(skill_status) && sizeof(skill_status))
        {
                int ob;

                if( objectp(ob=query_temp("weapon", me)) )
                        ob->unequip();

                delete_temp("handing", me);

                sname  = keys(skill_status);

                for (i = 0; i < sizeof(sname); i++)
                {
                        if (SKILL_D(sname[i])->type() != "martial")
                                continue;

                        if (sname[i] == "zuoyou-hubo")
                                continue;

                        if (sname[i] == "martial-cognize" || sname[i] == "sword-cognize")
                                continue;

                        if (sname[i] == "count" && tmpint >= 30)
                                continue;

                        for (j = 0; j < sizeof(valid_types); j++)
                        {
                                if (SKILL_D(sname[i])->valid_enable(valid_types[j]))
                                {
                                        switch(valid_types[j])
                                        {
                                        case "sword" :
                                                weapon = new("/clone/weapon/changjian");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "blade" :
                                                weapon = new("/clone/weapon/changjian");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "staff" :
                                                weapon = new("/clone/weapon/zhubang");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "whip" :
                                                weapon = new("/clone/weapon/changbian");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "club" :
                                                weapon = new("/clone/weapon/qimeigun");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "hammer" :
                                                weapon = new("/clone/weapon/hammer");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "throwing" :
                                                weapon = new("/d/tangmen/obj/qinglianzi");
                                                weapon->move(me, 1);
                                                set_temp("handing", weapon, me);
                                                break;
                                        default :
                                                break;
                                        }
                                        break;
                                }
                        }
                        if (! SKILL_D(sname[i])->valid_learn(me))
                        {
                                if (objectp(weapon))
                                        destruct(weapon);

                                return notify_fail(HIR "请输入 yanjiu " + sname[i] + " 1，确认可以研究后再洗新天赋。\n" NOR);
                        }

                        if (objectp(weapon))
                                destruct(weapon);
                }
        }
        */

        write("你重新分配的天赋为\n"
              "膂力[" + tmpstr + "]\n"
              "悟性[" + tmpint + "]\n"
              "根骨[" + tmpcon + "]\n"
              "身法[" + tmpdex + "]。\n");

        my["str"] = tmpstr;
        my["int"] = tmpint;
        my["con"] = tmpcon;
        my["dex"] = tmpdex;
        
        /*
        write(HIW "开始检查新天赋下所学技能是否满足学习条件...\n" NOR);
        
        if (mapp(skill_status) && sizeof(skill_status))
        {
                int ob;

                if( objectp(ob=query_temp("weapon", me)) )
                        ob->unequip();

                delete_temp("handing", me);

                sname  = keys(skill_status);

                for (i = 0; i < sizeof(sname); i++)
                {
                        if (SKILL_D(sname[i])->type() != "martial")
                                continue;

                        if (sname[i] == "zuoyou-hubo")
                                continue;

                        if (sname[i] == "martial-cognize" || sname[i] == "sword-cognize")
                                continue;

                        if (sname[i] == "count" && tmpint >= 30)
                                continue;

                        for (j = 0; j < sizeof(valid_types); j++)
                        {
                                if (SKILL_D(sname[i])->valid_enable(valid_types[j]))
                                {
                                        switch(valid_types[j])
                                        {
                                        case "sword" :
                                                weapon = new("/clone/weapon/changjian");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "blade" :
                                                weapon = new("/clone/weapon/changjian");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "staff" :
                                                weapon = new("/clone/weapon/zhubang");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "whip" :
                                                weapon = new("/clone/weapon/changbian");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "club" :
                                                weapon = new("/clone/weapon/qimeigun");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "hammer" :
                                                weapon = new("/clone/weapon/hammer");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "throwing" :
                                                weapon = new("/d/tangmen/obj/qinglianzi");
                                                weapon->move(me, 1);
                                                set_temp("handing", weapon, me);
                                                break;
                                        default :
                                                break;
                                        }
                                        break;
                                }
                        }
                        if (! SKILL_D(sname[i])->valid_learn(me))
                        {
                                if (objectp(weapon))
                                        destruct(weapon);
                                        
                                my["str"] = str;
                                my["int"] = wux;
                                my["con"] = con;
                                my["dex"] = dex;
                                return notify_fail(HIR "新天赋不能满足" + to_chinese(sname[i]) + "学习条件，修改失败。\n" NOR);
                        }

                        if (objectp(weapon))
                                destruct(weapon);
                }
        }
        */
        addn("gift/washed", 1, me);

        write("你重新分配你的天赋成功，请输入指令(hp -g)查看。\n");
        destruct(this_object());
        return 1;
}
