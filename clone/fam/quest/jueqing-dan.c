#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "绝情丹" NOR, ({ "jueqing dan", "jueqing", "dan" }) );
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "这是一颗鲜红色的丹药，外观甚是美丽，据说能解情花之毒。\n" NOR);
                set("value", 500000);
                set("unit", "颗");             
        }
        setup();
}

int query_autoload()
{
        return 1;
}