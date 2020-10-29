inherit DREAM_NPC;
#include <ansi.h>

int is_snake(){return 1;}
void create()
{
        set_name(HIG "五步蛇" NOR, ({ "wubu she", "wubu", "she" }));
        set("long", HIG "五步蛇是福建地方毒蛇，相传中毒行路五步即行倒毙。\n" NOR);

        set("age", 1);
        set("str", 15);
        set("dex", 40);
        set("max_qi", 4000);
        set("max_jing", 4000);
        set("combat_exp", 10000);
                set("max_neili", 25000);
                set("neili", 25000);

        set("snake_poison", ([
                "level"  : 50,
                "perhit" : 25,
                "remain" : 50,
                "maximum": 50,
                "supply" : 2,
        ]));

         set("no_nuoyi", 1); // 不被挪移影响
         
        set("power", 20);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/herb/shedan");

        set_temp("apply/dodge", 120);
        set_temp("apply/defense", 120);
        set_temp("apply/unarmed_damage", 80);
        set_temp("apply/armor", 120);

                set("gift/exp", 30);
                set("gift/pot", 20);
                set("oblist", ([
                        "/clone/herb/shedan" : 200,
                        "/clone/fam/gift/hong-feihun" : 2,
                        "/clone/armor/fenghuang-chai" : 20,
                        "/clone/armor/fenghuang-chai2" : 10,
                        "/clone/armor/fenghuang-chai3" : 6,                        
                        "/clone/armor/zhanshen-toukui":60,
                        "/clone/armor/zhanshen-toukui2":40,
                        "/clone/armor/zhanshen-toukui3":30,                                        
                        "/clone/armor/haizhi-xin":20,
                        "/clone/armor/haizhi-xin2":10,
                        "/clone/armor/haizhi-xin3":8,        
                        "/clone/tattoo/dizhangtu": 10,                        
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