// This program is a part of NT MudLIB 
// Written by Lonely@nitan.org
 
#include <ansi.h>
#include <armor.h>
 
inherit WAIST;
 
void create()
{
        set_name(HIY "神" HIW "之" HIM "祝福" NOR YEL "束带" NOR, ({ "zhufu waist", "waist", "shudai" }) );
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("long", "这是一条皮质的护腰，用以保护腰部。\n");
                set("value", 1000); 
                set("material", "cloth");
                set("armor_prop/armor", 20);
        }
        
        set("auto_load", 1); 
        set("mod_mark", "A2013");  
        set("mod_level", "M2010");  
        set("mod_name", HIY"神"HIW"之"HIM"祝福"NOR YEL"套装"NOR); 

        set("enchase", ([ 
                "flute" : 1,
                "used" : 1,
                "apply_prop" : ([ /* sizeof() == 2 */
                        "armor" : 30,
                        "int" : 1,
                ]),
        ]));

        set("insert", ({ /* sizeof() == 1 */
                ([
                        "id" : "magic stone",
                        "name" : HIM"玄石"NOR,
                        "apply_prop" : ([ /* sizeof() == 2 */
                                "armor" : 30,
                                "int" : 1,
                        ]),
                ]),
        }));
        
        set("require", ([
                "max_level" : 40,
                "max_age"   : 30,
        ]));
        set("quality_level", 2); 
        setup();
}

