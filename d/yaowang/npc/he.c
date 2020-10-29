#include <ansi.h>
inherit NPC;

void create()
{
        set_name(HIW"鹤"NOR, ({ "he"}) );
        set("race", "野兽");
        set("age", 4);
        set("long", "一只白色的鹤，头顶的红斑特别显眼。\n");
        set("attitude", "peaceful");
 
        set("str", 30);
        set("cor", 26);

        set("limbs", ({ "头部", "身体", "爪子", "翅膀"}) );
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
        object ob;
        message_vision(HIR"$N扑棱了两下翅膀，倒在地上，$N死了。\n"NOR, this_object());
        if(random(10)>8)
        {
        ob = new(__DIR__"obj/hedinghong");
        ob->move(environment(this_object()));
        }
        destruct(this_object());
}