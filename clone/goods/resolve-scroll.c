#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "分解卷轴" NOR, ({ "resolve scroll", "scroll" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIM "分解卷轴用来分解动态装备中各种魔法属性元素。\n" NOR);
                set("unit", "张");
                set("value", 500000);
                set("no_sell", 1);
        }
        setup();
}

