// This program is a part of NT MudLIB

#include <ansi.h>
#define GIFT_NAME "天赋分配工具"
inherit ITEM;

int do_fen(string arg);

void create()
{
        set_name(HIR + GIFT_NAME + NOR, ({"gift allocate"}));
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "件");
                set("long", @LONG
可以把mygift获得的先天天赋分（fen）到你想要的先天属性上
格式为 fen 悟性 1 这种格式。
LONG );
                set("value", 0);
                /*
                set("no_give", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_put", 1);
                set("no_sell", 1);
                set("no_drop", 1);
                */
        }
        setup();
}

void init()
{
        object me = this_player();

        if (me == environment())
        {
                add_action("do_fen", "fen");
        }
}

int do_fen(string arg)
{
        string htsx;
        int jnd;

        object me = this_player();

        if (! arg || sscanf(arg, "%s %d", htsx, jnd) != 2)
                return notify_fail("指令格式：fen <先天属性> <点数>\n");

        if( query("tianfu", me)<1 )
                return notify_fail("你目前没有剩下任何的先天天赋点数可用来分配！\n");

        if (htsx != "膂力" && htsx != "悟性" && htsx != "根骨" && htsx != "身法"
                && htsx != "str" && htsx != "int" && htsx != "con" && htsx != "dex")
                return notify_fail("你只可以将先天天赋点数分配到膂力、悟性、根骨和身法这四种天赋属性上！\n");

        if (jnd < 1) return notify_fail("先天天赋点数的分配每次最少要求是１点。\n");

        if( jnd>query("tianfu", me) )
                return notify_fail("你没有那么多的先天天赋点数！\n");

        switch (htsx)
        {
        case "膂力":
        case "str":
                addn("str", jnd, me);
                tell_object(me, HIY "冥冥中，你似乎感觉有一道光芒射入你的体内！\n" NOR);
                tell_object(me, HIG "你的「" + HIR + "先天膂力" + NOR + HIG "」提升了 " + HIR + chinese_number(jnd) + NOR + HIG + " 点！\n" NOR);
                break;
        case "悟性":
        case "int":
                addn("int", jnd, me);
                tell_object(me, HIY "冥冥中，你似乎感觉有一道光芒射入你的体内！\n" NOR);
                tell_object(me, HIG "你的「" + HIR + "先天悟性" + NOR + HIG "」提升了 " + HIR + chinese_number(jnd) + NOR + HIG + " 点！\n" NOR);
                break;
        case "根骨":
        case "con":
                addn("con", jnd, me);
                tell_object(me, HIY "冥冥中，你似乎感觉有一道光芒射入你的体内！\n" NOR);
                tell_object(me, HIG "你的「" + HIR + "先天根骨" + NOR + HIG "」提升了 " + HIR + chinese_number(jnd) + NOR + HIG + " 点！\n" NOR);
                break;
        case "身法":
        case "dex":
                addn("dex", jnd, me);
                tell_object(me, HIY "冥冥中，你似乎感觉有一道光芒射入你的体内！\n" NOR);
                tell_object(me, HIG "你的「" + HIR + "先天身法" + NOR + HIG "」提升了 " + HIR + chinese_number(jnd) + NOR + HIG + " 点！\n" NOR);
                break;
        default:
                return notify_fail("指令格式：fen <先天属性> <点数>\n");
                break;
        }
        addn("tianfu", -jnd, me);

        if( query("tianfu", me)<1 )
        {
                delete("tianfu", me);
                destruct(this_object());
        }

        if( query("tianfu", me)>0 )
                tell_object(me,HIG"你目前还有"+chinese_number(query("tianfu", me))+"点先天天赋没有分配！\n\n"NOR);
        return 1;
}

void owner_is_killed() { destruct(this_object()); }
