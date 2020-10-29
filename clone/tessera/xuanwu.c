#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIB "玄武·水" NOR, ({"xuan wu", "water"}));
        set_weight(20);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIB "可用于镶嵌10LV，属性水。\n" NOR);
                set("value", 100000);
                set("unit", "块");
                set("level", 4);
                set("no_identify", 1);
        }
        setup();
}