inherit DREAM_NPC;
#include <ansi.h>

int is_snake(){return 1;}

void create()
{
        set_name(HIR "腹蛇" NOR, ({ "fu she", "fu", "she" }));
        set("long", HIR "只见它全身血红，头呈三角，长蛇吞吐，嗤嗤做响。\n" NOR);

        set("age", 3);
        set("str", 35);
        set("dex", 50);
        set("max_qi", 3500);
        set("max_jing", 3500);
        set("combat_exp", 150000);
                set("max_neili", 25000);
                set("neili", 25000);
        set("snake_poison", ([
                "level"  : 220,
                "perhit" : 30,
                "remain" : 80,
                "maximum": 200,
                "supply" : 10,
        ]));

        set("power", 22);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/herb/shedan");

        set_temp("apply/parry", 300);
        set_temp("apply/dodge", 300);
        set_temp("apply/attack", 680);
        set_temp("apply/defense", 200);
        set_temp("apply/unarmed_damage", 900);
        set_temp("apply/armor", 100);
        set_temp("apply/attack", 85);
        set_temp("apply/damage", 600);
        set_temp("apply/armor", 200);
        set_temp("apply/defence",80);

                set("gift/exp", 30);
                set("gift/pot", 15);
                set("oblist", ([
                        "/clone/fam/gift/int2" : 200,
                        "/clone/fam/gift/int3" : 5,
                        "/clone/armor/feima-xue2" : 4,
                        "/clone/armor/feima-xue3" : 2,
                        "/clone/armor/biyu-chai" : 30,
                        "/clone/armor/biyu-chai2" : 20,
                        "/clone/armor/biyu-chai3" : 10,
                        "/clone/armor/huangtoujin":60,
                        "/clone/armor/huangtoujin2":40,
                        "/clone/armor/huangtoujin3":30,                                        
                        "/clone/armor/tie-shoutao":60,
                        "/clone/armor/tie-shoutao2":40,
                        "/clone/armor/tie-shoutao3":30,        
                ]));

        setup();
                add_money("silver", 2 + random(4));
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