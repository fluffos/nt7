// waiter.c

inherit KNOWER; 
inherit F_VENDOR;
#include <ansi.h>;

void create()
{
        set_name("唐小二", ({ "tang xiaoer", "tang", "waiter", "xiao er" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long",
                "这位唐小二正笑咪咪地忙著，还不时拿起挂在脖子上的抹布擦脸。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "小二哥");
        set("vendor_goods", ({
                "/clone/weapon/dagger",
                "/clone/food/jiudai",
                "/clone/food/baozi",
                "/clone/food/jitui",
        }) );
        setup();
}

void init()
{       
        object ob;
        mapping myfam;
        
        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) 
        {
                myfam=query("family", ob);
                if ( myfam && myfam["family_name"]== "唐门世家")
                {
                        remove_call_out("saying");
                        call_out("saying",1,ob);
                }
        
                remove_call_out("welcoming");
                call_out("welcoming", 1, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void welcoming(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
                
        switch( random(2) ) 
        {
                case 0:
                        say( "唐小二笑咪咪地说道：这位" + RANK_D->query_respect(ob)
                                + "，进来喝杯茶，歇歇腿吧。\n");
                        break;
                case 1:
                        say( "唐小二用脖子上的毛巾抹了抹手，说道：这位" + RANK_D->query_respect(ob)
                                + "，请进请进。\n");
                        break;
        }
}

void saying(object ob)
{
        if (!ob || environment(ob) != environment()) return;
        tell_object(ob,"唐小二笑咪咪地说道：这位"+RANK_D->query_respect(ob)+"，欢迎来到"GRN"唐门客店"NOR"\n\n");
        set_temp("rent_paid", 1, ob);
                
}

int accept_object(object who, object ob)
{
                
        if( query("money_id", ob) && ob->value() >= 5000 )
        {
                tell_object(who, "唐小二一哈腰，说道：多谢您老，客官请上楼歇息。\n");

                set_temp("rent_paid", 1, who);

                return 1;
        }

        return 0;
}

