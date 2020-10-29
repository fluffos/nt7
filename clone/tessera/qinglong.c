#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIG "青龙·木" NOR, ({"qing long", "wood"}));
        set_weight(20);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIG "可用于镶嵌10LV，属性木。\n" NOR);
                set("value", 100000);
                set("unit", "块");
                set("level", 4);
                set("no_identify", 1);
        }
        setup();
}