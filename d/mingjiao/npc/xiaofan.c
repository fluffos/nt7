// xiaofan.c 小贩子

inherit KNOWER;
inherit F_DEALER;
#include <ansi.h>

void create()
{
        set_name("小贩子", ({ "xiao fan", "xiao", "fan" }) );
        set("gender", "男性" );
        set("age", 34);
        set("long", "这是个小贩，别看他长的老老实实，可你别想从他那儿掏便宜。\n");
        set("combat_exp", 300);
        set("attitude", "peaceful");
        set("rank_info/respect", "小贩子");
        set("vendor_goods", ({
                "/d/mingjiao/obj/book",
                "/d/village/npc/obj/stick",
                "/d/village/npc/obj/shoes",
                "/d/village/npc/obj/bottle",
        }));
        setup();
}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch(random(2)){
          case 0:
          say(CYN"小贩子笑咪咪地说道：这位"+RANK_D->query_respect(ob)+"，要明教简史吗？\n"NOR);
          break;
          case 1:
          break;
        }
}
