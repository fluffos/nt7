#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(WHT "玄冰·寒铁" NOR, ({"ice steel", "han tie", "tie"}));
        set_weight(50);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", WHT "一块亮晶晶的金属，据说是在上古玄冰中孕育\n"
                                "出的寒铁。拥有无穷的魔力，上古神物，已经\n"
                                "通灵。\n" NOR);
                set("value", 10000000);
                set("unit", "块");
                set("can_be_tessera", 1);
                set("magic/type", "water");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5));
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_water" : 3,
                "add_skill" : 30,
                "research_effect" : 3,
                "practice_effect" : 3,
                "derive_effect" : 3,
        ]));
        set("enchase/armor_prop", ([
                "reduce_fire"  : 1,
                "research_effect" : 3,
                "practice_effect" : 3,
                "derive_effect" : 3,
        ]));
        setup();
}

int query_autoload() { return 1; }
