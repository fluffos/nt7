void init()
{
        object me, ob;
        mapping fam;
        ::init();
        ob = this_player();
        me = this_object();
        if (interactive(ob) && userp(ob)
         && !query("no_fight", environment(ob) )
        && !present("tieyan ling", ob) 
         && ((fam=query("family", ob)) && fam["family_name"] != "明教")){
             if( !query_temp("warned", ob)){
                   command("say 你是谁？  怎么闯到光明顶里来了？！");
                   command("say 快给我速速离开，下次看到决不轻饶！");
                   set_temp("warned", 1, ob);
                   }
              else if( query_temp("stay", ob)<3)addn_temp("stay", 1, ob);
              else {
                   command("say 大胆狂徒，竟敢闯到明教来撒野！！！\n");
                   remove_call_out("hiting_ob");
                   call_out("hiting_ob", 1, ob);
                   }
        }       
}
int hiting_ob(object ob)
{
     object me;
     me=this_object();
     if(objectp(ob) && present(ob, environment(me)) && 
        !query("no_fight", environment(me))){
        me->set_leader(ob);
        ob->kill_ob(me);
        me->fight_ob(ob);
        remove_call_out("moving_ob");
        call_out("moving_ob",1,ob);
        }
      else if( query("startroom", me))me->move(query("startroom", me));
      else return 0;
}

void moving_ob(object ob)
{
        if (!ob) return;
     if (!living(ob)){
        switch( random(3) ) {
           case 0: command("say 哼，看你以后还敢不敢乱闯光明顶！！！"); break;
           case 1: command("say 交给冷大人处理吧，关他一年半月的。"); break;
           case 2: command("nod"); break;
           }
        ob->move("/d/mingjiao/jianyu");
        }
     else{
        remove_call_out("hiting_ob");
        call_out("hiting_ob",1,ob);
        }
}
