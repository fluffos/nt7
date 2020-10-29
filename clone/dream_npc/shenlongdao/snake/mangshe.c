inherit DREAM_NPC;
#include <ansi.h>

int is_snake(){return 1;}

void create()
{
        set_name(HIG "蟒蛇" NOR, ({ "mang she", "mang", "she" }));
        set("long", HIG "这是一只昂首直立，吐着长舌芯的大蟒蛇。\n" NOR);

        set("age", 6);
        set("str", 250);
        set("dex", 20);
        set("con", 50);
                set("max_qi", 15000);
                set("max_jing", 15000);
                set("max_neili", 25000);
                set("neili", 25000);
        set("combat_exp", 300000);
                
                
        set("power", 45);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/quarry/item/shepi");

        set_temp("apply/force", 200);
        set_temp("apply/parry", 200);
        set_temp("apply/dodge", 200);
        set_temp("apply/attack", 180);
        set_temp("apply/defense", 180);
        set_temp("apply/unarmed_damage", 220);
        set_temp("apply/armor", 220);

                set("gift/exp", 60);
                set("gift/pot", 30);
                set("oblist", ([
                        "/clone/fam/gift/str2" : 100,
                        "/clone/fam/gift/dex3" : 3,
                        "/clone/armor/xingyue-erhuan" : 20,
                        "/clone/armor/xingyue-erhuan2" : 10,
                        "/clone/armor/xingyue-erhuan3" : 6,                        
                        "/clone/armor/shengling-yaodai":60,
                        "/clone/armor/shengling-yaodai2":40,
                        "/clone/armor/shengling-yaodai3":30,                                        
                        "/clone/armor/longshen-toukui":20,
                        "/clone/armor/longshen-toukui2":10,
                        "/clone/armor/longshen-toukui3":8,        
                ]));

        setup();
                add_money("silver", 5 + random(6));
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