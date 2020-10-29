inherit DREAM_NPC;
#include <ansi.h>

int is_snake(){return 1;}

void create()
{
        set_name(NOR + YEL "金蛇" NOR, ({ "jin she", "jin", "she" }));
        set("long", YEL "这是一条几寸长的小蛇，通体金黄。\n" NOR);

        set("age", 15);
        set("str", 30);
        set("dex", 50);
        set("con", 30);
                set("max_qi", 9000);
                set("max_jing", 9000);
                set("max_neili", 25000);
                set("neili", 25000);
        set("combat_exp", 30000000);

        set_skill("unarmed", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        set_skill("force", 300);

         set("no_nuoyi", 1); // 不被挪移影响
         
        set("snake_poison", ([
                "level"  : 300,
                "perhit" : 100,
                "remain" : 250,
                "maximum": 250,
                "supply" : 150,
        ]));
                set("gift/exp", 60);
                set("gift/pot", 30);
                set("oblist", ([
                        "/clone/fam/gift/str2" : 100,
                        "/clone/armor/suomai" : 10,
                        "/clone/armor/wushi-pifeng" : 20,
                        "/clone/armor/wushi-pifeng2" : 10,
                        "/clone/armor/wushi-pifeng3" : 6,                        
                        "/clone/armor/shenwu-xiangquan":60,
                        "/clone/armor/shenwu-xiangquan2":30,
                        "/clone/armor/shenwu-xiangquan3":10,                                        
                        "/clone/armor/yinyang-erhuan":20,
                        "/clone/armor/yinyang-erhuan2":10,
                        "/clone/armor/yinyang-erhuan3":8,        
                        "/clone/tattoo/changetu": 40,                        
                ]));

        set_temp("apply/attack",  300);
        set_temp("apply/unarmed_damage", 200);
        set_temp("apply/defense", 600);
        set_temp("apply/armor",   200);

        setup();
                add_money("silver", 5 + random(6));
}

void unconcious()
{
        this_object()->die();
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