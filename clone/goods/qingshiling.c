
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "清师令" NOR, ({ "qingshi ling", "qingshi", "ling" }) );
        set_weight(100);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIG "可使用他用来清除(qingshi <门派>)脱离师门不良记录一个。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "块");
                set("auto_load", 1);
        }

        setup();
}

void init()
{
        add_action("do_qingshi", "qingshi");
}

int do_qingshi(string arg)
{
        object me;
        me = this_player();

        if( !arg ) return notify_fail("使用格式：qingshi <门派>，例如 qingshi 武当派\n");

        if( !query("detach/"+arg, me) )
                return notify_fail("你并没有脱离过该门派的记录啊！\n");

        delete("detach/"+arg, me);
        if( sizeof(query("detach", me)) < 1 )
                delete("detach", me);

        write(HIM "清师令使用成功，你的"+arg+"脱离记录清除了！\n" NOR);
        write(HIG "清师令画作一缕青烟逐渐消失了！\n" NOR);
        me->save();
        destruct(this_object());

        return 1;
}

