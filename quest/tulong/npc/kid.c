inherit NPC;
void create()
{
        set_name("弟弟", ({ "kid"}) );
        set("gender", "男性" );
        set("age", 5);
        set("title", "精灵族小孩");
        set("long",
                "他光着身子，眉清目秀，可爱之极。\n");
        set("combat_exp", 50000);
        set("attitude", "friendly");
        set("per",15);
        set_skill("unarmed",50);
        set_skill("dodge",50);

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
}

void greeting(object ob)
{
        object  lianer;

        if( !ob || environment(ob) != environment() ) return;
        lianer = present("lian er", environment(ob));
        if(!objectp(lianer)){
message_vision("$N说：“莲儿姐唱的歌最好听了！”\n",this_object(),ob);
           return;
        }
        if(query_temp("marks/sing") == 1) {
           return;
        }
        switch( random(2) ) {
                case 0:
message_vision("$N摇着莲儿的手，说：“莲儿姐姐，唱个小调给我听吧。”\n",this_object(),ob);
                        break;
                case 1:
message_vision("$N缠着莲儿，说：“姐姐，我要听小曲儿！”\n",this_object(),ob);
                        break;
        }
        set_temp("marks/sing", 1, this_object());
        lianer->do_sing(ob);
}

int accept_object(object who, object ob)
{
   string       id;
   int          kar, c;
   object obj;

   id = ob->name(); 
   if( query("id", ob) == "fish"){
   message_vision("$N说道：“哇，好大的鱼！”\n",this_object()); 
   message_vision("$N说道：“多谢你啦，这个风筝送给你。”\n",this_object());
   obj=new("/quest/tulong/obj/kite");
   obj->move(this_player());
   return 1;
   }    
   message_vision("$N说道：＂多谢你啦!＂\n",this_object());
   if(id == "黄金" || id == "银子"){
     kar = (int)who->query_kar();
     c = (int)ob->value();
     if(random(c) > random(10000*(1000-kar*2))) {
        addn("score", 1, who);
     }
   }
   return 1;
}
