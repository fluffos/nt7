// animal: hudie.c

inherit NPC;

void create()
{
        set_name("蝴蝶", ({ "hu die", "hu" }) );
        set("race", "野兽");
        set("age", 4);
        set("long", "一只美丽的蝴蝶，看到它，你不觉有些感伤。\n");
        set("attitude", "peaceful");

        set("str", 26);
        set("cor", 30);

        set("limbs", ({ "前爪","嘴","后爪","翅膀" }));
        set("verbs", ({ "bite" }) );

        set("combat_exp", 800);

        setup();
}

void die()
{
        message_vision("$N轻轻地飘落在地面！$N无声无息地死了。\n", this_object());
        destruct(this_object());
}

