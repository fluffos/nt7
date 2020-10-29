#include <ansi.h>
inherit NPC;

void create()
{
        set_name(HIB"黑熊"NOR, ({ "hei xiong", "xiong" }) );
        set("race", "野兽");
        set("age", 4);
        set("long", "一只高大的黑熊，非常雄壮。\n");
        set("attitude", "peaceful");
 
        set("str", 30);
        set("cor", 26);

        set("limbs", ({ "头部", "身体", "爪子"}) );
        set("verbs", ({ "bite" }) );
 
        set("combat_exp", 3000);

        set_temp("apply/attack", 50);
        set_temp("apply/damage", 10);
        set_temp("apply/defence",30);
        set_temp("apply/armor",10);

        set("yaowang_zhuo",1);
        setup();
}

void die()
{
        object ob1, ob2, ob3;
        message_vision(HIR"$N身体一歪，倒在地上，$N死了。\n"NOR, this_object());
        if(random(10)>8)
        {
        ob1 = new(__DIR__"obj/xiongdan");
        ob2 = new(__DIR__"obj/xiongzhang");
        ob3 = new(__DIR__"obj/xiongzhang");
        ob1->move(environment(this_object()));
        ob2->move(environment(this_object()));
        ob3->move(environment(this_object()));
        }
        destruct(this_object());
}