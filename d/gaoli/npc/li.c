// 大唐双龙传
 
// xiaoer.c

inherit NPC;
inherit F_DEALER;

void create()
{
       set_name("李老板", ({"li laoban","li","laoban"}));
       set("shop_id",({"li laoban","li","laoban"}));
       set("shop_title","小吃店老板");
       set("gender", "男性");
        set("combat_exp", 1000);
       set("age", 26);
       set("per", 14);
       set("attitude", "friendly");
       set("shen_type", 1);
       set_skill("unarmed", 10);

        set("vendor_goods", ({
                "/d/gaoli/obj/jiudai",
                "/d/gaoli/obj/niangao",
                "/d/gaoli/obj/jitui",
        }));
       setup();
  carry_object("/d/gaoli/obj/cloth")->wear();
}

void init()
{
  ::init();

        add_action("do_buy", "buy");
        add_action("do_list", "list");
}
