// duck.c

inherit NPC;

void create()
{
        set_name("野鸭", ({ "duck" }) );
        set("race", "飞禽");
        set("age", 1);
        set("long", "一只野鸭。\n");
        set("limbs", ({ "头部", "身体", "尾巴" }) );
        set("verbs", ({ "bite" }) );

        set_skill("dodge", 50);
        set("combat_exp", 500);

        setup();
}

