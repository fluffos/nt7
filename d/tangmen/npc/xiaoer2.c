// xiaoer2.c 酒店小二

inherit KNOWER;
inherit F_DEALER;
#include <ansi.h>;
mixed do_ask(string arg);

void create()
{
        set_name("唐小一", ({ "tang xiaoyi", "tang", "xiaoyi" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long",
                "这位唐小一正笑咪咪地忙著，还不时拿起挂在脖子上的抹布擦脸。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("no_get", "1");
        set("rank_info/respect", "小一哥");
        set("vendor_goods", ({
                "/clone/food/jiudai",
                "/clone/food/meat",
                "/clone/food/peanut",
        }));
        set("inquiry", ([ 
                "tangfei"   : (: do_ask :), 
        ])); 
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{       
        object ob; 
        
        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() ) 
        {
           remove_call_out("greeting");
           call_out("greeting", 1, ob);
                
        }

        add_action("do_buy", "buy");
        add_action("do_list", "list");
        add_action("do_ask", "wen");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(3) ) 
        {
                case 0:
                        say( "唐小一笑咪咪地说道：这位" + RANK_D->query_respect(ob)
                                + "，进来喝杯茶，歇歇腿吧。\n");
                        break;
                case 1:
                        say( "唐小一用脖子上的毛巾抹了抹手，说道：这位" + RANK_D->query_respect(ob)
                                + "，请进请进。\n");
                        break;
                case 2:
                        say ("这位客官，有什么事的话您就问小的一声，小的马上就到！\n");
                        break;        
        }
}

mixed do_ask(string arg)
{    
        object me;
        mapping myfam;
        
        me=this_player();
        myfam=query("family", me);
        
        // say(HIC"来啦，有事你尽管问吧！\n"NOR);
                
        if( query_temp("yiwen", me) )
                return "你烦不烦啊，都和你说过了，你还来问我，我现有什么都不知道了! \n";
         
        if ( !myfam || myfam["family_name"] != "唐门世家")
                return "这位"+RANK_D->query_respect(me)+"，你与本门素无来往，此话从何谈起！\n";
        
        if ( myfam["family_name"]=="唐门世家")
        {      
                set_temp("yiwen", 1, me);
                switch( random(2) )
                {
                   case 0:
                        tell_object(me, HIG"原来是自己人啊，请上楼，唐老板正好回来了！\n"NOR);
                        me->move("/d/tangmen/jiulou2");
                        set_temp("askxiao", 1, me);
                        break;
                   case 1:
                        tell_object(me, HIR"不巧啊，唐老板正好出门了，你过一阵再来吧！\n"NOR);
                        break;
                 }            
                        
        }
          
        set_temp("yiwen", 1, me);
        return "不知这位"+RANK_D->query_respect(me)+"问我家老板有什么事! \n";
}
