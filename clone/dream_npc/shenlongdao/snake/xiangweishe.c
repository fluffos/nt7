inherit DREAM_NPC;
#include <ansi.h>

int is_snake(){return 1;}

void create()
{
        set_name(HIY "响尾蛇" NOR, ({ "xiangwei she", "xiangwei", "she" }));
        set("long", RED "这是一条赤黄色的毒蛇，尾巴吃吃作响。\n" NOR);

        set("age", 90);
        set("str", 135);
        set("dex", 50);
        set("max_qi", 100000);
        set("max_ging", 100000);
                set("eff_jing", 100000);
                set("max_jing", 100000);
                set("jingli", 100000);
                set("max_jingli", 100000);
                set("jingli", 100000);
                set("eff_jingli", 100000);
        set("combat_exp", 500000000);
                set("max_neili", 25000);
                set("neili", 25000);

        set("snake_poison", ([
                "level"  : 350,
                "perhit" : 360,
                "remain" : 200,
                "maximum": 200,
                "supply" : 180,
        ]));

        set_temp("apply/parry", 350);
        set_temp("apply/dodge", 250);
        set_temp("apply/attack", 350);
        set_temp("apply/defense", 180);
        set_temp("apply/unarmed_damage", 580);
        set_temp("apply/armor", 380);

                set("gift/exp", 150);
                set("gift/pot", 50);
                set("oblist", ([
                        "/clone/fam/gift/dex3" : 2,
                        "/clone/fam/gift/con3" : 2,
                        "/clone/armor/hong-feihun" : 10,
                        "/clone/armor/hong-feihun2" : 6,                
                        "/clone/armor/piaoxue":30,
                        "/clone/armor/piaoxue2":20,
                        "/clone/armor/piaoxue3":10,                                        
                        "/clone/armor/zijinhua-erhuan":20,
                        "/clone/armor/zijinhua-erhuan2":10,
                        "/clone/armor/zijinhua-erhuan3":8,        
                ]));
        setup();
                add_money("silver", 8 + random(8));
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