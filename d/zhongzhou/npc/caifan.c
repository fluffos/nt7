inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("菜贩子", ({ "cai fan", "cai", "fan" }) );
        set("gender", "男性" );
        set("age", 32);
        set("long",
                "一个老实巴交的农民，卖些新鲜的蔬菜。\n");
        set("shen_type", 1);
        set("combat_exp", 10000);
        set("str", 10);
        set("dex", 10);
        set("con", 10);
        set("int", 10);
        set("attitude", "peaceful");
        set_skill("dodge",20);
        set_skill("unarmed",20);
        set("chat_chance", 10);
        set("chat_msg", ({
                "菜贩子叫道：卖新鲜的萝卜吆。\n",
                "菜贩子叫道：卖新鲜的胡萝卜吆。\n",
                "菜贩子叫道：卖新鲜的白菜吆。\n",
                "菜贩子叫道：卖新鲜的大葱吆。\n",
                "菜贩子叫道：卖新鲜的土豆吆。\n",
        }) );

        set("vendor_goods", ({
                __DIR__"obj/luobo",
                __DIR__"obj/huluobo",
                __DIR__"obj/baicai",
                __DIR__"obj/dacong",
                __DIR__"obj/tudou",
        }) );

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        add_money("coin", 80);
}