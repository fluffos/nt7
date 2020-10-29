inherit DREAM_NPC;

#define NAME    HIW "玄冰" HIR "赤" HIW "蟒" NOR
#include <ansi.h>

int is_snake(){return 1;}
void create()
{
        set_name(NAME, ({ "xuanbing chimang", "xuan", "bing", "xuanbing",
                          "chimang", "mang", "snake" }));
        set("long", HIW @LONG
这是一只雪山怪蛇，只见它通体雪白，眼如烈
炎。看来这个冰洞是它的巢穴。
LONG NOR);

        set("age", 15);
        set("str", 50);
        set("dex", 50);
        set("con", 100);
        set("max_qi", 152200);
        set("max_ging", 152200);
                set("eff_jing", 100000);
                set("max_jing", 100000);
                set("jingli", 100000);
                set("max_jingli", 100000);
                set("jingli", 100000);
                set("eff_jingli", 100000);
        set("combat_exp", 500000000);
                set("max_neili", 35000);
                set("neili", 35000);

         set("no_nuoyi", 1); // 不被挪移影响
         
        set_skill("unarmed", 500);
        set_skill("dodge", 500);
        set_skill("parry", 500);
        set_skill("force", 500);

        set("snake_poison", ([
                "level"  : 500,
                "perhit" : 200,
                "remain" : 300,
                "maximum": 300,
                "supply" : 230,
        ]));

        set("power", 300);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/herb/shedan");
        set("item3", "/clone/fam/pill/blood");

        set_temp("apply/attack",  500);
        set_temp("apply/unarmed_damage", 300);
        set_temp("apply/defense", 500);
        set_temp("apply/armor",   300);

                set("gift/exp", 200);
                set("gift/pot", 80);
                set("oblist", ([
                        "/clone/fam/pill/blood" : 200,
                        "/clone/herb/shedan" : 200,
                        "/clone/fam/gift/lan-feihun2" : 2,
                        "/clone/armor/moling-zhiyi" : 10,
                        "/clone/armor/moling-zhiyi2" : 6,
                        "/clone/armor/moling-zhiyi3" : 3,                        
                        "/clone/armor/lan-feihun":20,
                        "/clone/armor/lan-feihun2":10,
                        "/clone/armor/lan-feihun3":5,                                        
                        "/clone/armor/jinsi-beixin":20,
                        "/clone/armor/jinsi-beixin2":10,
                        "/clone/armor/jinsi-beixin3":8,        
                        "/clone/tattoo/baichuantu": 40,
                ]));
        setup();
                add_money("silver", 5 + random(20));
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