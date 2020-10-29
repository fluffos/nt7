// This program is a part of NT MudLIB 
// Written by Lonely@nitan.org
// boots.c 皮靴
 
#include <ansi.h>
#include <armor.h>
 
inherit BOOTS;
 
void create()
{
        set_name(HIY "神" HIW "之" HIM "祝福" NOR YEL "皮靴"NOR, ({ "zhufu boots", "pi xue", "xue", "boots" }) );
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "leather");
                set("unit", "双");
                set("long", "这是一双用上好牛皮作的皮靴，用以保护足部。\n");
                set("value", 1000);
                set("armor_prop/dodge", 20);
        }

        set("auto_load", 1); 
        set("mod_mark", "A2014");  
        set("mod_level", "M2010");  
        set("mod_name", HIY"神"HIW"之"HIM"祝福"NOR YEL"套装"NOR); 

        set("enchase", ([ 
                "flute" : 1,
                "used" : 1,
                "apply_prop" : ([ /* sizeof() == 2 */
                        "armor" : 30,
                        "dex" : 1,
                ]),
        ]));
        
        set("insert", ({ /* sizeof() == 1 */
                ([
                        "id" : "magic stone",
                        "name" : HIM"玄石"NOR,
                        "apply_prop" : ([ /* sizeof() == 2 */
                                "armor" : 30,
                                "dex" : 1,
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

