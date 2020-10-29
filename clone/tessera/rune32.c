//rune32.c

// Cham 查姆

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "符文" NOR, ({"rune32", "rune"}));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", "符文：平育贾奕符，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 32);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "add_damage"    : 10,
                ]));
                set("enchase/armor_prop", ([
                        "reduce_damage" : 3,   
                        "practice_effect" : 20,   
                        "derive_effect" : 20,   
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }