//rune33.c

// Zod薩德

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }

void create()
{
        set_name(HIW "符文" NOR, ({"rune35", "rune"}));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", "符文：玉清清微符，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 35);
                set("enchase/type", "all");
                set("enchase/consistence", 100);
                set("enchase/weapon_prop", ([
                        "add_skill" : 50,
                        "add_freeze" : 10,
                        "add_blind" : 10,
                ]));
                set("enchase/armor_prop", ([
                        "add_skill" : 7,
                        "avoid_freeze" : 3,
                        "avoid_blind" : 3,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }
