//rune28.c

// Lo 

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "符文" NOR, ({"rune28", "rune"}));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", "符文：秀乐禁上符，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 28);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "da_power"      : 15,              
                ]));
                set("enchase/armor_prop", ([
                        "armor"         : 1500,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }