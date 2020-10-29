#include <ansi.h>
inherit NPC;

void create()
{
        set_name(YEL"梅花鹿"NOR, ({ "meihua lu", "lu" }) );
        set("race", "野兽");
        set("age", 2);
        set("long", "一只可爱的梅花鹿，它的血是大补之物。\n");
        set("attitude", "peaceful");
 
        set("str", 30);
        set("cor", 26);

        set("limbs", ({ "头部", "身体", "爪子", "尾巴" }) );
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
        message_vision(HIR"$N两腿一蹬，$N死了。\n"NOR, this_object());
        
        if(random(10)>8)
        {
        
        ob1 = new(__DIR__"obj/luxue");
        ob2 = new(__DIR__"obj/lurong");
        ob3 = new(__DIR__"obj/lurong");
        ob1->move(environment(this_object()));
        ob2->move(environment(this_object()));
        ob3->move(environment(this_object()));
        } else 
        {
        ob1 = new(__DIR__"obj/luxue");
        ob1->move(environment(this_object()));
        }
        destruct(this_object());
}