inherit SMITH; 
#include <ansi.h>;

void create()
{
        set_name("唐兵兵", ({ "tang bingbing", "tang", "bingbing" }) );
        set("title",HIC "唐门暗器专卖店   店主" NOR);
        set("gender", "男性" );
        set("age", 22);
        set("long",
                "这是唐门专门卖兵器的小伙子，祖传的暗器专卖店的负责人。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("no_get", "1");
        set("vendor_goods", ({
                "/d/tangmen/obj/fhshi",
                "/d/tangmen/obj/tiejili",
                "/d/tangmen/obj/feidao",
                "/d/tangmen/obj/qinglianzi",
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{       
        object ob; 
        mapping myfam; 

        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() ) 
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }

        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) 
        {
                case 0:
                        say( HIC"唐兵兵笑咪咪地说道：这位" + RANK_D->query_respect(ob)
                                + "，来买暗器啊。\n"NOR);
                        break;
                case 1:
                        say( HIG"唐兵兵搓了搓手，说道：这位" + RANK_D->query_respect(ob)
                                + "，想买点什么啊。\n"NOR);
                        break;
        }
}
