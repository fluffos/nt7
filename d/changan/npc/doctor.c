// doctor.c

inherit BUNCHER; 
inherit F_DEALER;

void create()
{
        set_name("时九公", ({ "shi jiugong", "shi", "jiugong"}));
        set("str", 20);
        set("gender", "男性");
        set("title", "药铺掌柜");
        set("age", 66);
        set("long", "据说时九公原是江湖中的名医。\n");
        set("combat_exp", 250);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/changan/npc/obj/jinchuang",
                "/d/changan/npc/obj/yangjing",
        }));

        setup();
        carry_object("/d/changan/npc/obj/choupao")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
