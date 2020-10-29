//tangfeng@SJ 2004
//类似擂台的功能
//胡斐和苗人凤比武的场地

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "练武场");
	set("long", @LONG
这里是一个破旧的练武场。上千年的踩踏已使得这些石板如同镜子般平
整光滑。正中央放着一块大牌子(paizi)。
LONG
	);
  set("no_death", 1);
  set("no_get_from", 1);
  set("no_sleep_room", 1);

  set("item_desc", ([
  "paizi" : "\n准备好了后请打 OK 。如果要放弃比赛，请打 LEAVE 。\n\n",
  ]));
  setup();
}
void init()
{
	object me,ob;
	me = this_player();
	message_vision("$N急急忙忙地走进了练武场。\n", me);
	if (!userp(me)) return;
  add_action("do_leave", "leave");
	if (!me->query_temp("quest/雪山飞狐/武功/fight_id")) return;
	if (!(ob=present(me->query_temp("quest/雪山飞狐/武功/fight_id"),this_object()))) return;
	message_vision(HIG"\n$N对$n点了点头。\n"NOR,ob,me);
	this_object()->set_temp("biwu",1);
	add_action("do_ok", "ok");
	add_action("do_action", ({"dazuo", "tuna", "lian", "learn", "du", "steal", "hit",
                                  "kill", "fight", "study", "practice", "exercise", "halt", "ask","whisper",
	                          "quit", "save", "throw", "rumor", "tell", "mm", "reply",
	                          "chat", "rumor", "party", "shout", "suicide", "yield"}));
}

int do_action(string arg)
{
	if(!wizardp(this_player())){
		write("练武场上只能比武，请不要做不相关的事！\n");
		return 1;
	}
	else return 0;
}

int do_ok()
{
	object ob, me = this_player();
	if (!me->query_temp("quest/雪山飞狐/武功/fight_id")) return 0;
	if (!(ob=present(me->query_temp("quest/雪山飞狐/武功/fight_id"),this_object()))) return 0;
	if (!ob->query_temp("biwu")) return 0;
        if (this_object()->query_temp("biwu")==2) return 0;
        if (!this_object()->query_temp("biwu")) return 0;
	this_object()->set_temp("biwu",2);
	message_vision(HIR"\n$N做了个鞠："+RANK_D->query_self(ob)+"已经准备好了，愿接受任何挑战！\n"NOR, ob);
	message_vision(HIR"\n$N做了个鞠："+RANK_D->query_self(me)+"已经准备好了，愿接受任何挑战！\n"NOR, me);
  me->kill_ob(ob);
  ob->kill_ob(me);
  remove_call_out("check");
  call_out("check",1,me);
	return 1;
}
void check(object me)
{
	object room,obj,ob;
	if(!me || !living(me)||!present(me,this_object())||me->query("qi")<=1||me->query("jing")<=1||!me->query_temp("quest/雪山飞狐/武功/fight_id"))
	{
		remove_call_out("check");

		//npc动向
		if((ob=present("hu fei",this_object())))
		{
	  	 message_vision(HIW"\n$N一脸高傲的神态：竟然没人敢来挑战，看来"+RANK_D->query_self(ob)+"真是天下无敌了！\n\n"NOR, ob);
		 ob->remove_all_killer();
	  	 ob->delete_temp("biwu");
	  	 ob->delete_temp("quest/try_fight_id");
			 if (!(room = find_object("/d/huanghe/fendi")))
            room = load_object("/d/huanghe/fendi");
       if( !room ) destruct(ob);
       else
       {
       	 if(!present("hu fei",room))
       	 {
       	 	message_vision(HIY"$N急急忙忙地离开了练武场。\n"NOR, ob);
       	 	ob->move(room);
			ob->remove_all_killer();
       	 	message_vision("$N急急忙忙地来到了"+environment(ob)->query("short")+"。\n", ob);
       	 }
  	     else destruct(ob);
       }
    }
		if((ob=present("miao renfeng",this_object())))
		{
	  	 message_vision(HIW"\n$N一脸高傲的神态：竟然没人敢来挑战，看来"+RANK_D->query_self(ob)+"真是天下无敌了！\n\n"NOR, ob);
		 ob->remove_all_killer();
	  	 ob->delete_temp("biwu");
	  	 ob->delete_temp("quest/try_fight_id");
			 if (!(room = find_object("/d/lanzhou/zhenting")))
            room = load_object("/d/lanzhou/zhenting");
       if( !room ) destruct(ob);
       else
       {
       	 if(!present("miao renfeng",room))
       	 {
       	 	message_vision(HIC"$N急急忙忙地离开了练武场。\n"NOR, ob);
       	 	ob->move(room);
			ob->remove_all_killer();
       	 	message_vision("$N急急忙忙地来到了"+environment(ob)->query("short")+"。\n", ob);
       	 }
  	     else destruct(ob);
       }
    }
    //失败后的去所
    if(userp(me))
    {
    	if(present(me,this_object()))
    	{
       	me->remove_all_killer();
		    me->revive();
    		me->reincarnate();

	  	  message_vision(HIW"\n突然一道神光笼罩着$N，$N的精气神竟然全部恢复了！\n"NOR, me);
     	 	message_vision(HIY"$N急急忙忙地离开了练武场。\n"NOR, me);
        if(me->query_temp("quest/雪山飞狐/武功/fight_id")=="miao renfeng") me->move("/d/lanzhou/zhenting");
        else me->move("/d/huanghe/fendi");
    		tell_object(me,HIR"\n比赛失败！下次努力！\n"NOR);
  log_file("quest/FEIHU", sprintf("%s(%s) 较量失败。经验：%d。\n", me->name(1),me->query("id"),me->query("combat_exp")) );
    		message_vision("$N急急忙忙地来到了"+environment(me)->query("short")+"。\n", me);
    	}
    	else	tell_object(me,HIR"\n比赛如此不专心，怎能不失败？下次努力吧！\n"NOR);
    }
   	me->delete_temp("quest/雪山飞狐/武功/fight_id");
    this_object()->delete_temp("biwu");
	  return;
	}
	if (!(ob=present(me->query_temp("quest/雪山飞狐/武功/fight_id"),this_object())))
	{
		  remove_call_out("check");
      me->add("combat_exp",500+me->query_skill("force")*3/2);
      tell_object(me,HIC"\n经过一番苦斗，你发现自己的武功大有激进。你获得"+(500+me->query_skill("force")*3/2)+"点经验。\n"NOR);

            tell_room(environment(me),HIC"\n"+me->query("name")+"经过一番打斗，似乎武功大有长进。\n"NOR, ({ me }));
      me->set("quest/雪山飞狐/武功/time",time());
	  me->set("quest/雪山飞狐/武功/fight_exp",me->query("combat_exp"));
      me->remove_all_killer();
	  me->revive();
    	me->reincarnate();
	  	message_vision(HIW"\n突然一道神光笼罩着$N，$N的精气神竟然全部恢复了！\n\n"NOR, me);
     	message_vision(HIR"$N急急忙忙地离开了练武场。\n"NOR, me);
	  	if(me->query_temp("quest/雪山飞狐/武功/fight_id")=="hu fei")
	  	{
			if(!me->query("quest/雪山飞狐/武功/win_hu")) me->set("quest/雪山飞狐/武功/win_hu",1);
			else me->add("quest/雪山飞狐/武功/win_hu",1);
			log_file("quest/FEIHU", sprintf("%s(%s) 和胡斐较量获胜。获得经验奖励：%d。经验：%d。\n", me->name(1),me->query("id"),(500+me->query_skill("force")*3/2),me->query("combat_exp")) );
	  		if (!(room = find_object("/d/huanghe/fendi")))
                   room = load_object("/d/huanghe/fendi");
        obj=new("/d/huanghe/npc/hu-fei");
        if(!present("hu fei",room)) obj->move(room);
        me->move(room);
      }
	  	else if(me->query_temp("quest/雪山飞狐/武功/fight_id")=="miao renfeng")
	  	{
			if(!me->query("quest/雪山飞狐/武功/win_miao")) me->set("quest/雪山飞狐/武功/win_miao",1);
			else me->add("quest/雪山飞狐/武功/win_miao",1);
  log_file("quest/FEIHU", sprintf("%s(%s) 和苗人风较量获胜。获得经验奖励：%d。经验：%d。\n", me->name(1),me->query("id"),(500+me->query_skill("force")*3/2),me->query("combat_exp")) );
	  		if (!(room = find_object("/d/lanzhou/zhenting")))
                   room = load_object("/d/lanzhou/zhenting");
        obj=new("/d/lanzhou/npc/miaorenfeng");
        if(!present("miao renfeng",room)) obj->move(room);
        me->move(room);
      }
      else me->move("/d/xiangyang/damen");
    	message_vision("$N急急忙忙地来到了"+environment(me)->query("short")+"。\n", me);
    	me->delete_temp("quest/雪山飞狐/武功/fight_id");
      this_object()->delete_temp("biwu");
    	return;
	}
  call_out("check",1,me);
}

int do_leave()
{
	object ob,room,me = this_player();
  if(this_object()->query_temp("biwu")==2)
  {
  	tell_object(me,HIR"\n你正在比赛之中，无法退出比赛。\n"NOR);
  	return 1;
  }
  me->set("quest/雪山飞狐/武功/time",time());
  me->remove_all_killer();
	me->reincarnate();
	message_vision(HIW"\n$N深叹了一口气，退出比武场！\n\n"NOR, me);
	remove_call_out("check");
	if((ob=present("hu fei",this_object())))
	{
	  	 message_vision(HIW"\n$N一脸高傲的神态：竟然没人敢来挑战，看来"+RANK_D->query_self(ob)+"真是天下无敌了！\n\n"NOR, ob);
		 ob->remove_all_killer();
	  	 ob->delete_temp("biwu");
	  	 ob->delete_temp("quest/try_fight_id");
			 if (!(room = find_object("/d/huanghe/fendi")))
            room = load_object("/d/huanghe/fendi");
       if( !room ) destruct(ob);
       else
       {
       	 if(!present("hu fei",room))
       	 {
       	 	message_vision("$N急急忙忙地离开了练武场。\n", ob);
       	 	ob->move(room);
			ob->remove_all_killer();
       	 	message_vision("$N急急忙忙地来到了"+environment(ob)->query("short")+"。\n", ob);
       	 }
  	     else destruct(ob);
       }
  }
  if((ob=present("miao renfeng",this_object())))
	{
	  	 message_vision(HIW"\n$N一脸高傲的神态：竟然没人敢来挑战，看来"+RANK_D->query_self(ob)+"真是天下无敌了！\n\n"NOR, ob);
		 ob->remove_all_killer();
	  	 ob->delete_temp("biwu");
	  	 ob->delete_temp("quest/try_fight_id");
			 if (!(room = find_object("/d/lanzhou/zhenting")))
            room = load_object("/d/lanzhou/zhenting");
       if( !room ) destruct(ob);
       else
       {
       	 if(!present("miao renfeng",room))
       	 {
       	 	message_vision("$N急急忙忙地离开了练武场。\n", ob);
       	 	ob->move(room);
			ob->remove_all_killer();
       	 	message_vision("$N急急忙忙地来到了"+environment(ob)->query("short")+"。\n", ob);
       	 }
  	     else destruct(ob);
       }
  }
 	message_vision(HIY"$N急急忙忙地离开了练武场。\n"NOR, me);
  if(me->query_temp("quest/雪山飞狐/武功/fight_id")=="miao renfeng") me->move("/d/lanzhou/zhenting");
  else me->move("/d/huanghe/fendi");
  me->delete_temp("quest/雪山飞狐/武功/fight_id");
	message_vision("$N急急忙忙地来到了"+environment(me)->query("short")+"。\n", me);
   log_file("quest/FEIHU", sprintf("%s(%s) 中止较量。经验：%d。\n", me->name(1),me->query("id"),me->query("combat_exp")) );
  this_object()->delete_temp("biwu");
	return 1;
}
