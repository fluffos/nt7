//shangren

inherit NPC;

void create()
{
        set_name("商人", ({ "shangren"}) );
        set("gender", "男性" );
        set("age", 36);
        set("long", "这是一位从中原来的商人。\n");
        set("combat_exp", 10000);
        set("attitude", "friendly");
        set_skill("cuff", 30);
        set_skill("dodge", 50);
        set("chat_chance", 10);
        set("chat_msg", ({
                "商人心有余辜的说道：我几乎死在唐门的暗器下！\n",
        }) );
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                "商人说道：我有幸从唐门的暗器下生还，现在居然要死在路边！\n",
                }) );

        setup();
        add_money("silver", 50);
        carry_object("/clone/misc/cloth")->wear();
}
