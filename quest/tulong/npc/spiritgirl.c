inherit NPC; 
int ask_me();
void create()
{
        set_name("莲儿", ({ "lianer", "lian er"}) );
        set("gender", "女性" );
        set("age", 21);
        set("title", "精灵族女子");
        set("long",
        "莲儿唱得一口好曲儿，长得楚楚动人，绝不逊色人类的女子。\n");
        set("combat_exp", 5000);
        set("attitude", "friendly");
        set("per",30);
        set_skill("unarmed",30);
        set_skill("dodge",80); 
      set("inquiry", ([
            "精灵之王" : (: ask_me :),
            "唱曲" : "“我是唱着玩的，让你见笑了。”\n",
        ]) );

        setup();
   carry_object("/clone/cloth/cloth")->wear();
}

void do_sing(object ob)
{
   switch(random(2)) {
      case 0:
         message_vision("$N转过来对$n微微一笑。\n\n",this_object(),ob);
         break;
      case 1:
         message_vision("$N回头对$n轻轻一笑。\n\n",this_object(),ob);
         break;
   }
   set_temp("marks/song", random(2), this_object());
   set_temp("marks/songa", 0, this_object());
   call_out("singing",2, this_object());
}

int singing (object ob)
{
   int  song, songa; 
   object kid;
   remove_call_out("singing");
   song=query_temp("marks/song", ob);
   songa=query_temp("marks/songa", ob);
   switch(song) {
      case 0:
         switch(songa) {
            case 0:
               message_vision("$N清声唱道：\n",ob);
               message_vision("        一年老一年，一日没一日，一秋又一秋，一辈催一辈，\n",ob);
               set_temp("marks/songa", 1, ob);
   call_out("singing",2,ob);
               break;
            case 1:
               message_vision("        一聚一离别，一喜一悲。一榻一身卧，一生一梦里。\n",ob);
               set_temp("marks/songa", 2, ob);
   call_out("singing",2,ob);
               break;
            case 2:
               message_vision("        寻一夥相识，他一会咱一会，都一般相知，吹一回，唱一回。\n\n",ob); 
               kid = present("kid", environment(ob));
               if(objectp(kid)) {
                  delete_temp("marks/sing", kid);
               }               break;
         }
         break;
      case 1: 
         switch(songa) {
            case 0:
   message_vision("$N轻敲竹板，婉声唱道：\n",this_object());
   message_vision("  东边路、西边路、南边路。五里铺、七里铺、十里铺。\n",this_object());
               set_temp("marks/songa", 1, ob);
   call_out("singing",2,ob);
               break;
            case 1:
   message_vision("  行一步、盼一步、懒一步。霎时间天也暮、日也暮、云也暮，\n",this_object());
               set_temp("marks/songa", 2, ob);
   call_out("singing",2,ob);
               break;
            case 2:
   message_vision("  斜阳满地铺，回首生烟雾。兀的不山无数、水无数、情无数。\n",this_object());
               kid = present("kid", environment(ob));
               if(objectp(kid)) {
                  delete_temp("marks/sing", kid);
               } 
               break;
         }
         break;
   }
}

int ask_me()
{ 
       object me = this_player();
       remove_call_out("ask_for_help");

       command("say 你要见精灵之王？");
       command("shake");
       command("say 不可能的。她很少见外人。");
       call_out("ask_for_help",20); 

       return 1;
}

int ask_for_help()
{     
      object ob = this_object(); 
      object me = this_player();
      object where, obj;
      where=environment(me); 
      ob->move(where);command("tell"+query("id", me)+"不好了，三清湖有鱼怪出现。求你帮帮我们！");
      command("say 我这里有些东西，也许能派上用场。");
      obj=new("/quest/tulong/obj/string");
      obj->move(ob); 
      command("givestringto"+query("id", me));
      command("say 我家里的东西你请随意取用。请一定要制服鱼怪！");
   ob->set("inquiry",([
            "鱼怪" : "“听说它已经成了精，会吃人的。”\n", 
            "精灵之王" : (: ask_me :),
            "唱曲" : "“我是唱着玩的，让你见笑了。”\n",        ]));
      return 1;
}
