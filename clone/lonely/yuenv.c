#include <weapon.h>

inherit SWORD;
#include <ansi.h>

void create()
{
        set_name(HIR"越女"+HIY"朝阳"+HIC"剑"NOR, ({ "yuenv chaoyang jian", "yuenv jian","jian", "sword" }) );
        set_weight(8000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("weapon_prop/kar", 15);
                set("weapon_prop/int", 3);
                set("weapon_prop/str", 5);
                set("weapon_prop/sword", 50);
                set("unit", "把");
                set("value", 10000000);
                set("material", "steel");
                set("long", "一把赤红软剑，据说是战国时越女的随身佩剑，其锋利程度不下干将 莫邪。\n");
                set("wield_msg", HIR"一声脆响,$N手里无声无息的多了把赤红软剑.\n"NOR);
                set("wield_msg", HIR"空气突然变得沉闷..,但听...\n"
                                 HIB"锵........镪........呛................\n"
                                 HIY"阵阵清越龙吟声不断响起...连绵不绝,$N手里已多了把"HIR"赤红软剑.\n"NOR);
        }

        init_sword(500,2);
        setup();
}

int query_autoload() { return 1; }
