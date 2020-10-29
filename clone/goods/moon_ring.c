// This program is a part of NT MudLIB
// moon.c 月魄

#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(WHT "月魄" NOR, ({ "moon soul", "moon" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", WHT "太阴真火凝聚而成，月白色，能摄心定神，百邪不侵。。\n" NOR);
                set("value", 50000);
                set("unit", "块");
                set("can_enchant", "armor");
                set("can_be_enchased", 1);
                set("magic/type", "magic");
                set("magic/power", 500);
                set("auto_load", 1);
        }
        set("enchase",  ([ /* sizeof() == 5 */
                "rings_prop" : ([ /* sizeof() == 3 */
                        "research_effect" : 3,
                        "derive_effect"   : 3,
                        "practice_effect" : 3,
                        "add_magic"       : 3,
                ]),
                "type" : "rings",
                "SN" : 1 + random(9),
        ])) ;

        set("enchant", 1);
        set("set_data", 1);
        setup();
}

