#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "附魔卷轴" NOR, ({ "enchant scroll", "scroll" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIM "附魔卷轴用来辅助日魂月魄附魔属性用的，可确保附魔时装备不会销毁。\n" NOR);
                set("unit", "张");
                set("value", 500000);
                set("no_sell", 1);
        }
        setup();
}

