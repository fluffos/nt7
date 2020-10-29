//rune20.c

// Lem 蓝姆

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "符文" NOR, ({"rune20", "rune"}));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", "符文：始黄孝芒符，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 20);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "max_neili"     : 100000,
                ]));
                set("enchase/armor_prop", ([ 
                        "max_neili"     : 100000,  
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }