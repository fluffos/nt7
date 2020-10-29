//Cracked by Kafei
// taomu-jian.c
//maco 修改 26/8/99

#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(HIM"桃木剑"NOR,({ "taomu jian", "taomu", "jian" }) );
        set_weight(1000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("value", 0);
                set("material", "wood");
                set("long", "这是一柄三尺来长，手工制成的桃木剑，似乎不是一件好兵器。\n");
                set("wield_msg", "$N拿出一把$n，握在手中。\n");
                set("unequip_msg", "$N放下手中的$n。\n");
        }
        init_sword(3);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int exp1, exp2, bonus, gain;
        int int1, int2, age1, age2;
        float gain1, gain2, gain3;
        mapping fam1, fam2;
        object where;
        
        where = environment(me);
        fam1=query("family", me);
        fam2=query("family", victim);

        if (strsrch(file_name(where), "/d/taohua/") < 0)
                return; 

        if (!fam1 || fam1["family_name"] != "桃花岛")
                return;
        if (!fam2 || fam2["family_name"] != "桃花岛")
                return;

        if (!userp(victim)) 
                return;

        if( query("owner") != query("id", me) )
                return;


        exp1=query("combat_exp", me);
        exp2=query("combat_exp", victim);
        int1 = me->query_int();
        int2 = victim->query_int();
        age1=query("age", me);
        age2=query("age", victim);
        
        if (exp1 > exp2) gain1 = (int)(exp1/exp2);
                else gain1 = (int)(exp2/exp1);
        if (gain1 > 2) gain1 = 0;
        if (int1 > int2) gain2 = int1-int2;
                else gain2 = int2-int1;
        if (gain2 > 4) gain2 = 0;
        if (age1 > age2) gain3 = age1/age2;
                else gain3 = age2/age1;
        if (gain3 > 1.2) gain3 = 0.2;
        
        gain = (gain1+gain2)*gain3;
        if (gain > 3) gain = 3;
        gain = gain*(int2+int1)/40+random(2);
        bonus = (int)(gain+damage_bonus/100*gain);

        me->apply_condition("th_gain", me->query_condition("th_gain")+1);
        addn_temp("exp_gain", bonus/3, me);//原本是除以2
        set_temp("partner", victim->name(), me);
        set_temp("partner", me->name(), victim);
//        me->addn("combat_exp", (int)bonus);
        if( query("potential", victim)<query("max_potential", victim) )
                addn_temp("pot_gain", bonus/3, victim);//原本是除以2
//                victim->addn("potential", bonus);
        set_heart_beat(1);
        return;
}