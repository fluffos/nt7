// This program is a part of NT MudLIB
// sun.c 日魂

#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(RED "日魂" NOR, ({ "sun soul", "sun" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", RED "太阳真火凝聚而成，乌金色，能破邪怯魔，千军辟易。。\n" NOR);
                set("value", 50000);
                set("unit", "块");
                set("can_enchant", "weapon");
                set("can_be_enchased", 1);
                set("magic/type", "magic");
                set("magic/power", 500);
                set("auto_load", 1);
        }

        set("enchase",  ([ /* sizeof() == 5 */
                "weapon_prop" : ([ /* sizeof() == 3 */
                        "research_effect" : 3,
                        "derive_effect"   : 3,
                        "practice_effect" : 3,
                        "add_magic"       : 3,
                ]),
                "type" : "hands",
                "SN" : 1 + random(9),
        ])) ;

        set("enchant", 1);
        set("set_data", 1);
        setup();
}

