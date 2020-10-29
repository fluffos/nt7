
inherit BUNCHER;

inherit F_DEALER;

void create()
{
        set_name("杨永福", ({ "yang yongfu", "yang" }));
        set("title", "杂货铺老板");
        set("shen_type", 1);

        set("gender", "男性");
        set("age", 45);
        set("long",
                "杨老板是土生土长的扬州人，做了几十年的小买卖。\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/damage", 15);

        set("combat_exp", 40000);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/clone/cloth/cuttonp",
                "/clone/misc/sleepbag",
                __DIR__"obj/mabudai",
                __DIR__"obj/beixin",
                __DIR__"obj/kaolu",
                __DIR__"obj/toukui",
                __DIR__"obj/cycle",
                __DIR__"obj/surcoat",
                __DIR__"obj/shield",
                __DIR__"obj/huwan",
                __DIR__"obj/zhitao",
                __DIR__"obj/huyao",
                __DIR__"obj/caoxie",
                __DIR__"obj/pixue",
                __DIR__"obj/shoutao",
                __DIR__"obj/tieshou",
                __DIR__"obj/jinsijia",
                __DIR__"obj/yanzhi",
                "/d/xingxiu/obj/fire",
                "/clone/misc/huoba",
                "/d/item/obj/chanhs",
                "/d/city/obj/rrose",
                "/d/city/obj/yrose",
                "/clone/misc/wood",
                "/clone/misc/shoeshine",
                "/clone/misc/brush",
                "/clone/misc/yanhuo",
                "/clone/misc/diaogan",
                "/clone/misc/yuer",
                "/d/taohua/obj/bagua",
                            "/u/redl/obj/chutou2",  
                      "/u/redl/obj/chutou", 
                        "/u/redl/obj/cigarette", 
"/d/room/obj/paper",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_look", "kan");
}
