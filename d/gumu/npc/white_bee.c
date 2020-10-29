// white_bee.c        玉蜂群
// by April 01.09.01

#include <ansi.h>

inherit NPC;

void create()
{
        set_name(WHT"玉蜂群"NOR, ({ "yufeng qun","bees" }) );
        set("race", "昆虫");
        set("subrace", "飞虫");
        set("age", 1);
        set("long", "这是古墓派驯养的一群玉蜂，嗡嗡的，不知有多少。\n");
        set("str", 60);
        set("dex", 80);

        set("limbs", ({ "密集处", "稀薄处", "核心", "外围" }) );

        set("max_jing",1000);
        set("jing",1000);
        set("qi",1000);
        set("max_qi",1000);
        set("jingli",1000);
        set("max_jingli",1000);

        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("unarmed", 100);

        setup();
}

void init()
{
        add_action("do_attack", "attack");
}

void die()
{
        object ob;

        message_vision("\n$N终于都死了，地上白茫茫一片。\n", this_object());
        destruct(this_object());
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        object owner;
        object here = environment(me);

        if( (owner=present(query("owner", me),here))){
                addn("combat_exp", 2+random(3), owner);
                addn("potential", 1+random(3), owner);

                owner->improve_skill("qufeng", 20+random(20), 0);
        }

        victim->apply_condition("yufengdu", 5 + random(5) 
                + victim->query_condition("yufengdu"));
}

int do_attack(string arg)
{
        object env, obj, ob, me = this_player(),bees;
        string target_dir, dir, dest, victim;
        mapping exit;

        if (!arg) return 0;

        victim = arg;
        if( victim == query("id", me))return notify_fail("玉蜂群不知所措，只是围着你打转。\n");

        ob = present(victim, environment(me));
        bees = present("yufeng qun", environment(me));

        if (!ob) return notify_fail("这里并无此人！\n");

        message_vision(HIR "$N嘴里嗡嗡作声，指挥玉蜂群向$n攻去。\n" NOR, me, ob);

        if( query("owner") != me || query("race", ob) != "人类"
                 || query("family/family_name", ob) == "古墓派"){
                message_vision( "$N不知所措，只是围着你打转。\n" NOR, bees );
                return 1;
        }

        if( random(20) ){
                message_vision( HIW"只见$N发疯般向$n扑了过去。\n" NOR, bees, ob );
                bees->kill_ob(ob);
                me->want_kill(ob);
                ob->kill_ob(me);
        }
        else
                message_vision( "$N不知所措，只是围着你打转。\n" NOR, bees );

        return 1;
}
