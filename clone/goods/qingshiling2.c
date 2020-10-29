
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "高级清师令" NOR, ({ "qingshi ling2", "qingshi", "ling2" }) );
        set_weight(100);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIG "可使用他用来无损脱离师门一次，必须脱离前使用(use ling2)才有效。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "块");
                set("auto_load", 1);
        }

        setup();
}

void init()
{
        add_action("do_qingshi", "use");
}

int do_qingshi(string arg)
{
        object me;
        me = this_player();

        if( !arg ) return notify_fail("使用格式：use ling2\n");

        addn("skill_expell_penalty_tsl", 1, me);

        write(HIM "高级清师令使用成功，你增加了一次可以无损脱师的机会！\n" NOR);
        write(HIG "高级清师令化作一缕青烟逐渐消失了！\n" NOR);
        me->save();
        destruct(this_object());

        return 1;
}

