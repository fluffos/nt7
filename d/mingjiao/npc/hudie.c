// hudie.c

inherit NPC;

void create()
{
        set_name("蝴蝶", ({ "hudie"}) );
        set("race", "野兽");
        set("age", 3);
        set("long", "一只五颜六色的蝴蝶，十分可爱，是蝴蝶的珍品。\n");

        set("limbs", ({ "头部", "身体", "前爪", "后爪", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 100);
    
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 10);

        setup();
}
