#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIG "九地·玄玉" NOR, ({"xuan yu", "jiudi xuanyu", "jiudi", "xuanyu"}));
        set_weight(50);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIG "一块绿色的九地玄玉，拥有能医重病，又能毒\n"
                            "杀人于一身的至宝——九地玄玉，相传神农氏\n"
                            "所用神农尺就是用这枚九地玄玉精炼而成。上\n"
                            "古神物，已经通灵。\n" NOR);
                set("value", 10000000);
                set("unit", "块");
                set("can_be_tessera", 1);
                set("magic/type", "earth");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5));
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_earth" : 3,
                "add_skill" : 30,
                "research_effect" : 3,
                "practice_effect" : 3,
                "derive_effect" : 3,
        ]));
        set("enchase/armor_prop", ([
                "reduce_water" : 1,
                "research_effect" : 3,
                "practice_effect" : 3,
                "derive_effect" : 3,
        ]));
        setup();
}

int query_autoload() { return 1; }
