#include <ansi.h> 
inherit NPC; 

void create()
{
        set_name("接引使", ({"jieyin shi", "shi", "leader"}));
        set("age", 14);
        set("attitude", "peaceful");
        set("gender", "女性");
        set("title", "精灵使");
        set("str", 20);
        set("int", 20);
        set("per", 30);
        set("con", 20);
        set("max_qi",21000);
        set("max_jing", 21000);
        set("combat_exp", 101100000);

        set("neili", 9000);
        set("max_neili", 9000);
        set("jiali", 10);
        set_skill("unarmed", 700);
        set_skill("force", 800);
        set_skill("dodge", 800);
        set_skill("parry", 900);
        set_skill("blade", 900);
        setup();

} 

void init()
{
        object ob;

        ::init();
        
        if( interactive(ob=this_player()) && !is_fighting() )
        {
                // remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
         
        add_action("do_answer", "answer");
} 

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() )
                return; 
                
        if( query_temp("check_answer/" + query("id", ob)) ) {
                command("say 请你快回答吧。");
                return;
        }        
         
        switch(random(4)) {
        case 0 :
                say("接引使微笑道：这位" + RANK_D->query_respect(ob) +
                        "，请先回答我一个问题：如果你的母亲和妻子同时遇险，你会先救哪一个呢？\n");  
                set_temp("check_answer/"+query("id", ob), 1, this_object());
                call_out("say_answer", 30, ob);
                break;  
        case 1 :
                say("接引使微笑道：这位" + RANK_D->query_respect(ob) +
                        "，请先回答我一个问题：如果你的儿子和女儿同时遇险，你会先救哪一个呢？\n");
                set_temp("check_answer/"+query("id", ob), 1, this_object());
                call_out("say_answer", 30, ob);
                break;
        case 2 :
                say("接引使微笑道：这位" + RANK_D->query_respect(ob) +
                        "，请先回答我一个问题：如果你的妻子和朋友同时遇险，你会先救哪一个呢？\n");
                set_temp("check_answer/"+query("id", ob), 1, this_object());
                call_out("say_answer", 30, ob);
                break;
        case 3 :
                say("接引使微笑道：这位" + RANK_D->query_respect(ob) +
                        "，请先回答我一个问题：如果你的朋友和亲属同时遇险，你会先救哪一个呢？\n");                  
                set_temp("check_answer/"+query("id", ob), 1, this_object());
                call_out("say_answer", 30, ob);
                break;
        }
}

void say_answer(object who)
{
        if( !who || environment(who) != environment() ) return;
        command("smile");
        command("say 对了，沉默才是答案！这本来是没有答案的问题，一切要视当时的情形而定。" + 
                who->query_idname(1) + "过关了，去吧。\n");   
        delete_temp("check_answer/"+query("id", who), this_object());
        who->move("/d/dragon/spirit5");
        return ;
}
   
int do_answer(string arg)
{
        object me, ob;
        
        me = this_player();
        ob = this_object();
        
        if( !arg ) return notify_fail("你说什么？\n");

        if( !(query_temp("check_answer/" + query("id", me),ob)) )
                return notify_fail("什么？\n");


        message_vision("$N答道：我会先救“" + arg + "”。\n", me);

        if( arg == "亲属" || arg == "女儿" || arg == "儿子" || arg == "母亲" || arg == "妻子" || arg == "朋友" ) 
        {
                switch (random(3)) {
                case 0:      
                        message_vision("$N侧身让出一条路。\n", ob);   
                        delete_temp("check_answer/"+query("id", me), ob);
                        me->move("/d/dragon/spirit3");
                        remove_call_out("say_answer"); 
                        break;
                case 1: 
                        message_vision("$N侧身让出一条路。\n", ob);   
                        delete_temp("check_answer/"+query("id", me), ob);
                        me->move("/d/dragon/spirit4");  
                        remove_call_out("say_answer");
                        break;
                case 2: 
                        message_vision("$N侧身让出一条路。\n", ob);   
                        delete_temp("check_answer/"+query("id", me), ob);
                        me->move("/d/dragon/spirit0");
                        remove_call_out("say_answer");
                        break;
                } 
                return 1;
        }
        command("say 请认真回答！\n");
        return 1;
}

