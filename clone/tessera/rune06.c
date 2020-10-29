//rune06.c

// Ith 伊司

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "符文" NOR, ({"rune06", "rune"}));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", "符文：七曜摩夷符，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 6);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "ref_qi"  : 60,
                ]));
                set("enchase/armor_prop", ([
                        "ref_qi"  : 30,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }