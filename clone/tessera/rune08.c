//rune08.c

// Ral 拉

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "符文" NOR, ({"rune08", "rune"}));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", "符文：太极蒙翳符，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 8);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "max_jing"      : 5000,
                ]));
                set("enchase/armor_prop", ([
                        "max_jing"      : 5000,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }