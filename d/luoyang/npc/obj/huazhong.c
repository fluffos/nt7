#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(YEL "花种" NOR, ({"hua zhong", "hua", "zhong"}));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一枚无法确定品种的花种。\n");
                set("unit", "只");
                set("value", 1);
                set("food_remaining", 1);
                set("food_supply", 10);
        }
}

void init()
{
        add_action("do_zhonghua", "zhonghua");
}

int do_zhonghua()
{
        object me, ob, where;
 
        me = this_player();
        ob = this_object();
        where = environment(me);

        if( query("short", where) != "苗园" )
                return notify_fail("这里似乎不适合种花吧？\n");

        if( query("combat_exp", me)<8000 )
        {
                tell_object(me, "你的经验尚浅，还是先到处多走动走动吧。\n");
                return 1;
        }

        if( query("combat_exp", me)>30000 )
        {
                tell_object(me, "以你的身份大概不适合种花了吧。\n");
                return 1;
        }

        if( query_temp("zhonghua", me) == 1 )
        {
                tell_object(me, "种子已经拨下了，现在该培育"
                                HIY "(peiyu)" NOR "花种了。"
                                "\n");
                return 1;
        }

        message_vision(HIC "$N" HIC "用手在地上挖了一个小"
                       "坑，把花种放了进去。\n" NOR, me);
        tell_object(me, "种子已经拨下了，现在该培育" HIY
                        "(peiyu)" NOR "花种了。\n");
        addn_temp("zhonghua", 1, me);
        destruct(ob);
        addn("jing", -50, me);
        return 1;
}