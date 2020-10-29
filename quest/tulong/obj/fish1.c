inherit NPC;

void create()
{
        set_name("鱼怪", ({ "fish monster", "fish" }) );
        set("race", "野兽");
        set("age", 300);
        set("long", "这是一只身形很大，已成精怪的鱼，浑身覆满绚丽的鳞片，\n"
            "一口锋利的牙齿，正虎视耽耽的看着你\n");
        set("attitude", "aggressive");

        set("max_qi",10000); 
        set("max_jing",10000);
        set("max_neili",10000);
        set("str", 26);
        set("cor", 30); 
        set("dex", 30);
        set("limbs", ({ "头部", "身体", "腹部", "尾巴" }) );

        set("verbs", ({ "bite" }) );

        set("combat_exp", 500000);
        
        set_temp("apply/attack", 300);
        set_temp("apply/damage", 300);
        set_temp("armor", 800);
        setup();
}

void die()
{
        object ob;
        message_vision("$N口中吐出一粒内丹，肚皮往上一翻，$N死了。\n", this_object());
        ob = new("/quest/tulong/obj/neidan");
        ob->move(environment(this_object()));
        destruct(this_object());
}