#include <weapon.h>
#include <ansi.h>
#include <armor.h> 
inherit SWORD;

void create()
{
        set_name(NOR + CYN "娥眉剑" NOR, ({ "emei jian", "emei", "jian" }));
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", "这是一柄精金铁铸造的细剑，蜀山女弟子所配，剑刃锋利冷寒。\n");
                set("value", 3000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
        }
        set("weapon_prop/fatal_blow", 24);
        set("weapon_prop/add_forget", 3);
        //set("weapon_prop/avoid_defense", 8);
        set("weapon_prop/avoid_parry", 8);
        set("weapon_prop/avoid_dodge", 8);
        set("weapon_prop/avoid_force", 8);
        set("weapon_prop/avoid_attack", 8);
        
        init_sword(1200);
        setup();
}


