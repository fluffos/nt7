// 玄兵圣水用于开孔兵器

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "玄兵圣水" NOR, ({ "bored water", "water" }) );
        set_weight(30);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIW "一瓶莹剔透圣水，散射出绚目的光彩。\n"
                            "他可以用来最大化开孔兵器或防具。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "瓶");
        }

        setup();
}

int query_autoload()
{
        return 1;
}
