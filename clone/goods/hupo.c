#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIB "上古·虎魄" NOR, ({"tiger soul", "tiger", "soul"}));
        set_weight(50);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIB "\n一块蓝色的虎魄，无暇的表面射魄出奇幻的光\n"
                            "泽。其中仿佛蕴藏着无穷的魔力，这便是传说\n"
                            "中的至宝，凶中之凶的——上古虎魄，相传为\n"
                            "上古时代，蚩尤所得异物炼制而成。上古神物，\n"
                            "已经通灵。\n" NOR);
                set("value", 10000000);
                set("unit", "块");
                set("can_be_tessera", 1);
                set("magic/type", "wood");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5));
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_wood"  : 3,
                "add_skill" : 30,
                "research_effect" : 3,
                "practice_effect" : 3,
                "derive_effect" : 3,
        ]));
        set("enchase/armor_prop", ([
                "reduce_earth"  : 1,
                "research_effect" : 3,
                "practice_effect" : 3,
                "derive_effect" : 3,
        ]));
        setup();
}

int query_autoload() { return 1; }
