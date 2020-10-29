// gangdao.c
#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name(HIW"回风刀"NOR, ({ "wan dao","blade" }));
        set_weight(12000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", "这是一柄亮晃晃的钢刀，是大宋官兵的常备武器。\n");
                set("value", 1000);
                set("rigidity",200);
                set("no_get",1);
                set("no_put",1);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回刀鞘。\n");
        }
        init_blade(400);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
       object weapon = this_object();
       int dam;

       if( query("equipped", weapon) )
       {
                dam=query_temp("warquest/group", me)*query("weapon_prop/damage", weapon)/10;
                dam = dam/4+random(dam/3);
                victim->receive_damage("qi", dam, me);
                victim->receive_wound("qi", dam, me); 
       }
       return damage_bonus;
}

void owner_is_killed() { destruct(this_object()); }  