#include <ansi.h>
inherit NPC;

void create()
{
        set_name(HIG"眼镜蛇"NOR, ({ "yanjing she", "she" }) );
        set("race", "野兽");
        set("age", 2);
        set("long", "一条眼镜蛇，足有手臂粗细。\n");
        set("attitude", "peaceful");
 
        set("str", 30);
        set("cor", 26);

        set("limbs", ({ "头部", "身体", "尾巴" }) );
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
        object ob1, ob2;
        message_vision(HIR"$N倒在地上卷曲了两下身子，$N死了。\n"NOR, this_object());
        if(random(10)>8)
        {
        ob1 = new(__DIR__"obj/shedu");
        ob2 = new(__DIR__"obj/shedan");
        ob1->move(environment(this_object()));
        ob2->move(environment(this_object()));
        }
        destruct(this_object());
}