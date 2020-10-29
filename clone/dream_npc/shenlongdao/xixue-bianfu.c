inherit DREAM_NPC;
#include <ansi.h>

int is_quarry(){return 1;}
int is_not_hunting(){return 1;}

void create()
{
        set_name(HIR "吸血蝙蝠" NOR, ({ "xixue bianfu", "xixue", "bianfu" }));

        set("age", 20);
        set("str", 300);
        set("dex", 1000);
        set("max_qi", 10000);
        set("max_ging", 10000);
                set("eff_jing", 10000);
                set("max_jing", 10000);
                set("max_neili", 25000);
                set("neili", 25000);
                set("jingli", 10000);
                set("max_jingli", 10000);
                set("jingli", 10000);
                set("eff_jingli", 10000);
        set("combat_exp", 500000);


        set_temp("apply/parry", 350);
        set_temp("apply/dodge", 2000);
                set_temp("apply/dex", 200);
        set_temp("apply/attack", 2000);
        set_temp("apply/defense", 180);
        set_temp("apply/unarmed_damage", 3580);
        set_temp("apply/damage", 3000);
        set_temp("apply/armor", 380);

                set_skill("dodge", 100);
                set_skill("unarmed", 100);

                set("gift/exp", 20);
                set("gift/pot", 10);
                set("oblist", ([
                        "/clone/fam/gift/dex3" : 10,
                        "/clone/armor/feima-xue3" : 10,
                ]));
        setup();
                //add_money("silver", 6 + random(8));
}

mixed hit_ob(object me, object ob, int damage)
{
        mapping p;
        string  msg;
        int force;
        int dur;

        p=query("snake_poison", me);
        if (! p) return;
        if (damage / 3 + random(damage * 2 / 3) <
            query_temp("apply/armor", ob) )
        {
                // Defeated by armor
                return;
        }

        msg = "";
        dur = p["perhit"];
        if (dur > (int)p["remain"]) dur = p["remain"];
        p["remain"] = (int)p["remain"] - dur;
        this_object()->apply_condition("poison-supply", 1);
        if (! dur) return;


        force = (int)ob->query_skill("force");
        if (random(force / 2) + force / 2 >= (int)p["level"] &&
            query("neili", ob)>damage/5 )
        {
                if( query("qi", ob)<150 )
                {
                        msg = HIR "你觉得伤口有些发麻，连忙运功化解，但"
                              "是一时体力不支，难以施为。\n" NOR;
                } else
                if( query("jing", ob)<60 )
                {
                        msg = HIR "你觉得伤口有些发麻，连忙运功化解，但"
                              "是一时精神不济，难以施为。\n" NOR;
                } else
                if( query("neili", ob)<damage/5+50 )
                {
                        msg = HIR "你觉得伤口有些发麻，连忙运功化解，但"
                              "是一时内力不足，难以施为。\n" NOR;
                } else
                {
                        addn("neili", -damage/5, ob);
                        ob->receive_damage("qi", 20);
                        ob->receive_damage("jing", 10);
                        return HIM "你觉得被咬中的地方有些发麻，连忙运功"
                               "化解毒性。\n" NOR;
                }
        }

        if (ob->affect_by("poison", ([ "level" : (int)p["level"] / 2,
                                       "name"  : "蛇毒",
                                       "id"    : "nature poison",
                                       "duration" : dur / 2, ])))
        {
                msg += HIR "$n" HIR "脸色一变，只觉被咬中的地方一阵麻木。\n" NOR;
        }
        return msg;
}
