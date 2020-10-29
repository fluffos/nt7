// yizhanxiaoer.c 小二

inherit NPC;
#include <ansi.h>;

void create()
{
        set_name("驿站小二", ({"xiao er"}) );
        set("gender", "男性" );
        set("age", 22);
        set("long",
                "这位小二正笑咪咪地闲著，还不时拿起茶壶喝上两口。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("no_get", "1");
        set("rank_info/respect", "小二哥");
        set("chat_chance", 1 );
        set("chat_msg", ({
                (:command("say "+"有钱的坐坐车，没钱的跑跑腿。"):),
                ( : command("say "+"有钱你是大爷，没钱我是大爷。") : ),
                ( : command("say "+"价格公平合理，卖买自由竞争！") : ),
        }) );       
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
        
        add_action("do_kill", "hit");          
        add_action("do_kill", "fight");          
        add_action("do_kill", "kill");          
}       

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if( query("age", ob)<15)set_temp("paid_for", 1, ob);
                
        switch( random(2) ) 
        {
                case 0:
                        say( "小二笑咪咪地说道：这位" + RANK_D->query_respect(ob)
                                + "，到那儿去啊。\n");
                        break;
                case 1:
                        say( "小二喝了口茶，说道：这位" + RANK_D->query_respect(ob)
                                + "，长途旅行，本店优惠。\n");
                        break;
        }
}


int do_kill(string arg)
{    
            
        if ( arg == "xiao er" || arg == "xiaoer" )
        return 1;    
        return 0;    
}

int accept_object(object who, object ob)
{
        
        if( query("money_id", ob) && ob->value() >= 2000 )
        {
                tell_object(who, "小二一哈腰，说道：多谢您老，请您老雇车。\n");

                set_temp("paid_for", 1, who);

                return 1;
        }

        return 0;
}            
