// crossbow.c

#include <ansi.h>

inherit __DIR__"bow";

void create()
{
        set_name(HIY "盘古巨弓" NOR, ({ "pangu gong", "pangu", "gong" }));
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "张");
                set("long", HIY "一张看似非凡的巨弓。\n" NOR);
                                set("value", 500000);
                set("accuracy", 300);   // 准确度150%
        }
        setup();
}

int query_autoload()
{
        return 1;
}