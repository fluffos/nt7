//rune33.c

// Zod薩德

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }

void create()
{
        set_name(HIW "符文" NOR, ({"rune36", "rune"}));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", "符文：无极大罗符，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 36);
                set("enchase/type", "all");
                set("enchase/consistence", 100);
                set("enchase/weapon_prop", ([
                        "add_forget" : 10,
                        "add_weak"   : 5,
                        "fatal_blow" : 10,
                ]));
                set("enchase/armor_prop", ([
                        "avoid_forget" : 3,
                        "avoid_weak" : 3,
                        "avoid_die" : 3,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }
