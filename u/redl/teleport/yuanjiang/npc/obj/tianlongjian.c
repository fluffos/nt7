#include <weapon.h>
#include <ansi.h>
#include <armor.h> 
inherit SWORD;

void create()
{
        set_name(NOR + HIC "天龙" HIY "伏魔剑" NOR, ({ "tianlong jian", "jian" }));
        set_weight(1200);
                set("unit", "柄");
                set("long", "这是一柄精金铁铸造的细剑，蜀山齐霞儿所有，剑气光明正大。\n");
                set("value", 5000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
        set("weapon_prop/fatal_blow", 35);
        set("weapon_prop/add_forget", 7);
        set("weapon_prop/avoid_parry", 5);
        set("weapon_prop/avoid_dodge", 5);
        set("weapon_prop/avoid_force", 5);
        set("weapon_prop/avoid_attack", 5);
        init_sword(2500);
        setup();
}



