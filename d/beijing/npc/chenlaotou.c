inherit BUNCHER;

void create()
{
        set_name("陈老头", ({ "chen laotou", "chen", "laotou" }) );
         set("title", "客店老板");
        set("gender", "男性" );
        set("age", 32);
        set("long",
              "一个年过六旬的小老头，他就是这家小客店的老板。\n");
        set("shen_type", 1);
        set("combat_exp", 3000);
        set("str", 10);
        set("dex", 10);
        set("con", 10);
        set("int", 10);
        set("attitude", "peaceful");
        set_skill("dodge",10);
        set_skill("unarmed",10);
        set("chat_chance", 10);
        set("chat_msg", ({
                "陈老头苦笑着对你说道：这位客官，真是对不住，小店已经客满了。\n",
                "陈老头一边哼着小调一边拿着抹布打整卫生。\n",
                "陈老头一个人嘀咕道：桌子也该换得了。\n",
        }) );       

        setup();
        carry_object("/d/beijing/npc/obj/cloth")->wear();
        add_money("silver", 20);
}
