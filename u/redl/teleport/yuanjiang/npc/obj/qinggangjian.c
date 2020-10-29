#include <weapon.h>
#include <ansi.h>
#include <armor.h> 
inherit SWORD;

void create()
{
        set_name(NOR + HIG "青罡剑" NOR, ({ "qinggang jian", "jian" }));
        set_weight(1200);
                set("unit", "柄");
                set("long", "这是一柄精金铁铸造的细剑，蜀山齐灵云所有，剑刃锋利冷寒。\n");
                set("value", 5000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
        set("weapon_prop/fatal_blow", 32);
        set("weapon_prop/add_forget", 5);
        set("weapon_prop/avoid_parry", 3);
        set("weapon_prop/avoid_dodge", 3);
        set("weapon_prop/avoid_force", 3);
        set("weapon_prop/avoid_attack", 3);
        init_sword(1500);
        setup();
}



