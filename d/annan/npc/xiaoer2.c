inherit NPC;

void create()
{
   set_name("店小二",({ "xiao er","xiao","er" }) );
        set("gender", "男性" );
        set("age", 22);
   set("long", "这是这家小客栈的店小二，每天忙来忙去。\n");
       
   set("combat_exp", 200);
   set("no_get",1);
   set("str", 18);
   set("per", 22);
   set("attitude", "friendly");
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
  
}

void init()
{
        object ob,ob2;
        ob=this_player();
        ob2=this_object();
        ::init();
        if(!ob||!present(ob,environment())||ob2->is_fighting()) return;
        call_out("welcome",1,ob,ob2);
        
}

void welcome(object ob,object ob2)
{
   if(!ob||!present(ob,environment())||ob2->is_fighting()) return;
        switch(random(2))
        {
        case 0: message_vision("$N笑道:别看本客栈小，包您满意!\n",ob2);break;
        case 1: message_vision("$N朝$n笑道：这位客官请了!\n",ob2,ob);
        }
        remove_call_out("welcome");
        return;
}

int accept_object(object who,object ob)
{
        if( query("money_id", ob) && ob->value() >= 500 )
          if(random(10)>4)
        {tell_object(who,"店小二微笑道：这位客官，您请进去休息吧!\n");
         set_temp("gived_money", 1, who);
          }  else return notify_fail("店小二陪笑道：对不住，本店客满了，请客官到别处吧！\n");
    else tell_object(who,"店小二笑道：本店住宿，一晚5两白银.\n");
    return 1;
}