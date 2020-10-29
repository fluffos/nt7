#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIW "高头大马" NOR, ({"zhan ma", "horse", "ma"}));
        set("race", "野兽");
        set("age", 3);

        set("combat_exp", 500000);
        set("long", 
                "一匹高头大马，全身雪白的毛发，煞是神俊。\n");

        set("limbs", ({ "头部", "身体", "蹄子", "尾巴" }) );
        set("verbs", ({ "bite", "hoof" }) );

        set("str", 20+random(10));
        set("con", 20+random(5));
        set("dex", 20+random(5));
        set("age", 20+random(30));   
        set("ridable", 1); 
 
        set_temp("apply/attack", 3);
        set_temp("apply/defense", 5);
        set_temp("apply/armor", 1);

        set("ride_prop/dodge",100);
        set("ride_prop/defense",100);

        set("chat_chance", 5);
        set("chat_msg", ({
                 HIW"战马不住地低鸣，蹄子不挺地刨打着地面。\n"NOR,
        }) );

        setup();
}


void die()
{
        destruct(this_object());
        return;
}