// tangzg.c 唐掌柜 

inherit NPC;
inherit F_VENDOR;
//inherit F_DEALER;

void create()
{
        set_name("唐掌柜", ({ "tang zhanggui", "tang" }));
        set("title", "唐家铺子老板");
        set("shen_type", 1);

        set("gender", "男性");
        set("age", 45);
        set("long",
                "唐掌柜是唐门的家人，做了多年的买卖了。\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/damage", 15);

        set("combat_exp", 40000);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/tangmen/obj/beixin",
                "/d/tangmen/obj/huwan",
                "/d/tangmen/obj/zhitao",
                "/d/tangmen/obj/shoutao",
                
                
        }));
        
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

