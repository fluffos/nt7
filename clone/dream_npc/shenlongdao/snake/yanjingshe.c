inherit DREAM_NPC;
#include <ansi.h>

int is_snake(){return 1;}
void create()
{
        set_name(HIR "眼镜蛇" NOR, ({ "yanjing she", "yanjing", "she" }));
        set("long", HIR "这是一条五彩斑斓的眼镜蛇，毒性猛烈之极。\n" NOR);

        set("age", 3);
        set("str", 35);
        set("dex", 50);
        set("max_qi", 4800);
        set("max_jing", 4800);
        set("combat_exp", 200000);
                set("max_neili", 25000);

                set("neili", 25000);
        set("snake_poison", ([
                "level"  : 150,
                "perhit" : 50,
                "remain" : 80,
                "maximum": 80,
                "supply" : 3,
        ]));

        set("power", 28);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/herb/shedan");

        set_temp("apply/parry", 120);
        set_temp("apply/dodge", 120);
        set_temp("apply/attack", 120);
        set_temp("apply/defense", 180);
        set_temp("apply/unarmed_damage", 180);
        set_temp("apply/armor", 180);
                set("gift/exp", 30);
                set("gift/pot", 15);
                set("oblist", ([
                        "/clone/herb/shedan" : 100,
                        "/clone/fam/gift/lan-feihun" : 2,
                        "/clone/armor/feima-xue" : 20,
                        "/clone/armor/feima-xue2" : 10,
                        "/clone/armor/wuzhe-huwan3" : 1,                        
                        "/clone/armor/biyu-chai":60,
                        "/clone/armor/biyu-chai2":40,
                        "/clone/armor/biyu-chai3":30,                                        
                        "/clone/armor/yinyang-erhuan":10,
                        "/clone/armor/yinyang-erhuan2":4,
                        "/clone/armor/yinyang-erhuan3":2,        
                ]));
        setup();
                add_money("silver", 4 + random(8));
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