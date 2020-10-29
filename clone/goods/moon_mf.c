// This program is a part of NT MudLIB
// redl 2014

#include <ansi.h>

inherit TESSERA;

void create()
{
        int i = 8;
        set_name(NOR YEL "秘魔" WHT "邪眼" NOR, ({ "mimo xieyan", "mimo", "xieyan" }) );
        set_weight(1);
                set("long", WHT "能发现隐秘宝藏的妖怪的眼珠。\n" NOR);
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
                                set("enchase/armor_prop/reduce_busy", 1); 
                                set("enchase/weapon_prop/reduce_busy", 1); 
                        } else {
                                set("enchase/armor_prop/reduce_busy", 2); 
                                set("enchase/weapon_prop/reduce_busy", 2); 
                        }
                        break;
                case 1:
                        if (random(8)) {
                                set("enchase/armor_prop/avoid_busy", 1.0); 
                                set("enchase/weapon_prop/avoid_busy", 1.0); 
                        } else {
                                set("enchase/armor_prop/avoid_busy", 2.0); 
                                set("enchase/weapon_prop/avoid_busy", 2.0); 
                        }
                        break;
                default:
                                set("enchase/armor_prop/armor", (random(11)+10) * 10); 
                                set("enchase/weapon_prop/through_armor", 1.0); 
                        break;
        }
        
                set("enchase/weapon_prop/magic_find", 3.0); 
                set("enchase/armor_prop/magic_find", 3.0); 
                
                if (!random(15)) {
                        set("enchase/weapon_prop/avoid_weak", 1.0); 
                    set("enchase/armor_prop/avoid_weak", 1.0); 
                }
                if (!random(15)) {
                        set("enchase/weapon_prop/avoid_freeze", 1.0); 
                    set("enchase/armor_prop/avoid_freeze", 1.0); 
                }
                if (!random(15)) {
                        set("enchase/weapon_prop/avoid_forget", 1.0); 
                    set("enchase/armor_prop/avoid_forget", 1.0); 
                }
                
        while (i--) {
                if (random(i+1) > 0 ) {
                                addn("enchase/armor_prop/magic_find", 1.0); 
                                addn("enchase/weapon_prop/magic_find", 1.0); 
                        } else
                        break;
                }
        
        
}

