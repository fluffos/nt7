//rune23.c

// Mal 马尔

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "符文" NOR, ({"rune23", "rune"}));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", "符文：上揲阮乐符，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 23);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "practice_effect"     : 20,
                ]));
                set("enchase/armor_prop", ([
                        "practice_effect"     : 5,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }