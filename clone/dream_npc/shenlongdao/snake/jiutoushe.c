inherit DREAM_NPC;
#include <ansi.h>

int is_snake(){return 1;}

void create()
{
        set_name(HIR "九头蛇" NOR, ({ "jiutou she", "jiutou", "she" }));
        set("long", HIR "这是一只巨大的毒蛇，长有九个头，形状十分可怕。\n" NOR);

        set("age", 90);
        set("str", 300);
        set("dex", 200);
        //set("max_qi", 2992200);
        set("max_qi", 11000);
        //set("eff_qi", 2992200);
        set("eff_qi", 11000);
        //set("eff_jing", 1100000);
        set("eff_jing", 7000);
        //set("max_jing", 1100000);
        set("max_jing", 7000);
        //set("jingli", 1100000);
        set("jingli", 7000);
        //set("max_jingli", 1100000);
        set("max_jingli", 7000);
        //set("combat_exp", 5000000000);
        set("combat_exp", 80000000);
        set("max_neili", 650000);
        set("neili", 650000);

        set("no_nuoyi", 1); // 不被挪移影响

        set("snake_poison", ([
                "level"  : 600,
                "perhit" : 460,
                "remain" : 400,
                "maximum": 400,
                "supply" : 350,
        ]));

        set_temp("apply/parry", 150);
        set_temp("apply/dodge", 350);
        set_temp("apply/attack", 150);
        set_temp("apply/defense", 380);
        set_temp("apply/unarmed_damage", 680);
        set_temp("apply/armor", 580);

        //set("end_time", 3);
        set("gift/exp", 4000);
        set("gift/pot", 1000);
        set("gift/mar", 100);
        set("gift/gold", 20);

        //set("gift/lvl", 145);
        set("oblist", ([
                "/clone/fam/gift/str4" :1,
                "/clone/fam/gift/con4" :1,                        
                "/clone/armor/moling-zhiyi3" : 3,                        
                "/clone/armor/zhanhun-xue3":20,
                "/clone/armor/xingyue-erhuan3":20,
                "/clone/fam/item/wannian-hong":30,
        ]));
        setup();
        //add_money("gold", 5);
}

void init()
{
        object ob, me;

        me = this_player();
        ob = this_object();

        ::init();
        if( interactive(me) && visible(me) &&
            !is_fighting()) {
                //NPC_D->copy_from_me(ob, me, 10, 1);
                kill_ob(me);
        }
}

/*
mixed hit_ob(object me, object ob, int damage)
{
        mapping p;
        string  msg;
        int force;
        int dur;

        p = query("snake_poison", me);
        if (! p) return;
        if (damage / 3 + random(damage * 2 / 3) <
            (int)query_temp("apply/armor", ob))
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
            query("neili", ob) > damage / 5)
        {
                if (query("qi", ob) < 150)
                {
                        msg = HIR "你觉得伤口有些发麻，连忙运功化解，但"
                              "是一时体力不支，难以施为。\n" NOR;
                } else
                if (query("jing", ob) < 60)
                {
                        msg = HIR "你觉得伤口有些发麻，连忙运功化解，但"
                              "是一时精神不济，难以施为。\n" NOR;
                } else
                if (query("neili", ob) < damage / 5 + 50)
                {
                        msg = HIR "你觉得伤口有些发麻，连忙运功化解，但"
                              "是一时内力不足，难以施为。\n" NOR;
                } else
                {
                        ob->add("neili", -damage / 5);
                        if( query("neili", ob) < 0 )
                                set("neili", 0, ob);
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
*/
