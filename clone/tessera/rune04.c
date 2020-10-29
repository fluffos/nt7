//rune04.c

// Nef 那夫

#include <ansi.h>

inherit TESSERA;

int is_rune() { return 1; }
 
void create()
{
        set_name(HIW "符文" NOR, ({"rune04", "rune"}));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", "符文：玄胎平育符，可以放入凹槽物品。\n");
                set("unit", "个");
                set("enchase/SN", 4);
                set("enchase/type", "all");
                set("enchase/consistence", 100); 
                set("enchase/weapon_prop", ([
                        "practice_times"       : 40,
                ]));
                set("enchase/armor_prop", ([
                        "practice_times"       : 20,
                ]));
                set("value", 20000);
        }
        setup();
}

int query_autoload() { return 1; }