// This program is a part of NT MudLIB
// redl 2014

#include <ansi.h>

inherit TESSERA;

void create()
{
                int i = 10;
        set_name(NOR YEL "肉身" WHT "菩提" NOR, ({ "roushen puti", "roushen", "rou" }) );
        set_weight(1);
                set("long", WHT "肉身菩萨身上的瘤子(类似乔丹之石)。。\n" NOR);
                set("value", 50000);
                set("unit", "块");
                set("can_enchant", "all");
                set("can_be_enchased", 1);
                //set("magic/type", "magic");
                //set("magic/power", 500);
                set("auto_load", 1);
        set("enchase",  ([
                "armor_prop" : ([
                                "armor" : 100,
                ]),
                "weapon_prop" : ([
                                "armor" : 100,
                ]),
                "type" : "all",
                "SN" : 0,
        ])) ;

        set("enchant", 1);
        set("set_data", 1);
        setup();
        switch ( random(5) ) {
                case 0:
                        if (random(8)) {
                                set("enchase/armor_prop/reduce_damage", 1); 
                                set("enchase/weapon_prop/reduce_damage", 1); 
                        } else {
                                set("enchase/armor_prop/reduce_damage", 2); 
                                set("enchase/weapon_prop/reduce_damage", 2); 
                        }
                        break;
                case 1:
                        if (random(6)) {
                                set("enchase/armor_prop/add_skill", random(2)+1); 
                                set("enchase/weapon_prop/add_skill", random(2)+1); 
                        } else {
                                set("enchase/armor_prop/add_skill", random(2)+3); 
                                set("enchase/weapon_prop/add_skill", random(2)+3); 
                        }
                        break;
                default:
                                set("enchase/armor_prop/armor", (random(11)+10) * 10); 
                                set("enchase/weapon_prop/armor", (random(11)+10) * 10); 
                        break;
        }
                set("enchase/weapon_prop/max_qi", 500000); 
                set("enchase/weapon_prop/max_jing", 250000); 
                set("enchase/armor_prop/max_qi", 500000); 
                set("enchase/armor_prop/max_jing", 250000); 
        while (i--) {
                if (random(i * 5) > 3 ) {
                                addn("enchase/armor_prop/max_qi", 2000 * i); 
                                addn("enchase/armor_prop/max_jing", 1000 * i); 
                                addn("enchase/weapon_prop/max_qi", 2000 * i); 
                                addn("enchase/weapon_prop/max_jing", 1000 * i); 
                        } else
                        break;
                }
        
        
}

