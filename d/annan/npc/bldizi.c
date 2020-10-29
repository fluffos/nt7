inherit NPC;

void create()
{
   set_name("安南帮弟子",({ "dizi"}) );
        set("gender", "男性" );
        set("age",30+random(10));
   set("long", "这是安南帮的弟子。据说安南帮以贩卖人口为主，\n"+
               "所以姑娘妇人都远远地躲着他们。\n");       
   set("combat_exp", 50000);
   set_skill("parry",50);
   set_skill("dodge",50);
   set_skill("force",50);
   set_skill("unarmed",50);
   set_skill("cuff",50);

   set("attitude", "peaceful");
   set("chat_chance",20);
   set("chat_msg",({
       (:random_move:),
   }));
   set("max_kee",100);
   set("target",1);
   add_money("coin",50);
   setup();
 
}

void init()
{
   object ob;
   ob=previous_object();
   if(userp(ob)&&!ob->is_fighting()&&living(ob))
    call_out("welcome",0,ob);
}

void welcome(object ob)
{
   if(!ob||!living(ob)||
   environment(ob)!=environment(this_object()))
   return;
   if( query("gender", ob) == "女性"){
     if( query("class", ob) == "bonze" )
       message_vision("$N朝$n打量了几眼:原来是个尼姑！真是倒霉！！\n",
           this_object(),ob);
     else
     message_vision("$N朝$n上上下下打量着，不知道在打着什么鬼主意。\n",
           this_object(),ob);}
   else
    message_vision("$N冷冷地看了看$n",this_object(),ob);
    
   return;
}
