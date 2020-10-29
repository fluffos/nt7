#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIC "地心·噬魂" NOR, ({"shi hun", "dixin shihun", "dixin", "shihun"}));
        set_weight(50);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIC "一块青色的地心噬魂，拥有集天下万毒及邪能\n"
                            "于一身的至宝——地心噬魂，相传为邪灵之主\n"
                            "罗刹到九幽之底，掘出当年被女娲消灭的异兽\n"
                            "骸骨，以地心毒火精炼而成。上古神物，已经\n"
                            "通灵。\n" NOR);
                set("value", 10000000);
                set("unit", "块");
                set("can_be_tessera", 1);
                set("magic/type", "fire");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5));
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_fire"  : 3,
                "add_skill" : 30,
                "research_effect" : 3,
                "practice_effect" : 3,
                "derive_effect" : 3,
        ]));
        set("enchase/armor_prop", ([
                "reduce_metal" : 1,
                "research_effect" : 3,
                "practice_effect" : 3,
                "derive_effect" : 3,
        ]));
        setup();
}

int query_autoload() { return 1; }
