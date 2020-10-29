#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIY "上古·太虚" NOR, ({"tai xu", "tai", "xu"}));
        set_weight(50);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIY "一块金黄色的太虚，拥有无穷变化的魔力，这\n"
                            "便是传说中的至宝——上古太虚，相传为上古\n"
                            "时代，黄帝得九天玄女所送南北精铁炼制而成。\n"
                            "上古神物，已经通灵。\n" NOR);
                set("value", 10000000);
                set("unit", "块");
                set("can_be_tessera", 1);
                set("magic/type", "metal");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5));
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_metal" : 3,
                "add_skill" : 30,
                "research_effect" : 3,
                "practice_effect" : 3,
                "derive_effect" : 3,
        ]));
        set("enchase/armor_prop", ([
                "reduce_wood" : 1,
                "research_effect" : 3,
                "practice_effect" : 3,
                "derive_effect" : 3,
        ]));
        setup();
}

int query_autoload() { return 1; }
