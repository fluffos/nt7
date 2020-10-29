inherit NPC;
inherit F_DEALER;

void create()
{
   set_name("店小二",({ "xiao er","xiao","er" }) );
        set("gender", "男性" );
        set("age", 22);
   set("long", "这是这家酒馆的店小二。\n");
    set("shop_id",({ "xiao er","xiao","er" }) );
   set("combat_exp", 2000);
   set("str", 18);
   set("per", 22);
   set("attitude", "friendly");

        set("vendor_goods", ({
                __DIR__"obj/jiudai",
                __DIR__"obj/huasheng",
                "/d/city/npc/obj/baozi",
        }));   
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
  
}

void init()
{
        ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}
