// wugong.c

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("蜈蚣", ({ "wugong", "gong", "wu" }) );
        set("race", "野兽");
        set("age", 2);
        set("long", "一只赤红色的毒蜈蚣，竟有一尺来长。\n");
        set("attitude", "peaceful");

        set("limbs", ({ "头部", "背壳", "尾钳" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 25000);
        set_temp("apply/attack", 3);
        set_temp("apply/defense", 5);
        set_temp("apply/armor", 15);

        setup();
}

int hit_ob(object me, object ob, int damage)
{
//        if ((int)ob->query("combat_exp") > 100000) return 1 ;
        if( query("combat_exp", ob)>100000)return 1;
        if( random(damage)>query_temp("apply/armor", ob) && ob->query_condition("xie_poison")<20 )
        {
                ob->apply_condition("xie_poison", 40);
                tell_object(ob, HIG "你觉得被刺中的地方一阵麻木！\n" NOR );
        }
}

void die()
{
        object ob;
        message_vision("$N背壳“啪”的一声破裂了，身体抽动了几下，死了。\n", this_object());
//        ob = new(__DIR__"xiezike");
//        ob->move(environment(this_object()));
        destruct(this_object());
}
