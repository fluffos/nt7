//chen-laoban

inherit BUNCHER; 
inherit F_DEALER;

void create()
{
        set_name("陈老板", ({ "chen laoban", "chen","laoban" }));
        set("title", "首饰店老板");
        set("shop_id", ({"laoban"}));
        set("gender", "男性");
        set("shen_type", 1);
        set("age", 43);
        set("combat_exp", 100000);
        set("attitude", "friendly");
        set("str", 30);
        set("max_qi", 300);
        set("max_jing", 300);
        set("neili", 300);
        set("max_neili", 300);
        set("jiali", random(10)+15);
        set_skill("unarmed", 30);
        set_skill("parry", 40);
        set_skill("dodge", 40);
        set("vendor_goods", ({
                "/d/changan/npc/obj/yinjie",
                "/d/changan/npc/obj/zuanjie",
                "/d/changan/npc/obj/baojie",
                "/d/changan/npc/obj/jinjie",
                "/d/changan/npc/obj/baijie",
        }));

        setup();
        carry_object("/d/changan/npc/obj/choupao")->wear();
}

void init()
{
        ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}
