//yang-laoban.c

inherit BUNCHER;
inherit F_DEALER;

void create()
{
        set_name("杨老板", ({ "yang laoban", "yang","laoban" }));
        set("title", "望星楼老板");
        set("shen_type", 1);
        set("str", 24);
        set("gender", "男性");
        set("age", 55);
        set("long", "杨老板不但是这儿的掌柜，还是这儿的大厨，\n并且烧得一手好菜。\n");
        set("combat_exp", 50000);
        set("attitude", "friendly");
        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set("vendor_goods", ({
                "/d/changan/npc/obj/zuixunfeng",
                "/d/changan/npc/obj/snxiangji",
                "/d/changan/npc/obj/lhjiyu",
        }));

       setup();
       carry_object("/d/changan/npc/obj/choupao")->wear();
       add_money("silver", 50);
}

void init()
{
       add_action("do_buy", "buy");
       add_action("do_list", "list");         
}
