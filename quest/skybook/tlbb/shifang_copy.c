//tangfeng@SJ 2004
//类似擂台的功能
// /d/shaolin/shifang_copy.c
// 复兴天下最后一战，没有死亡危险，但难度很大

#include <ansi.h>
inherit ROOM;
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"

void create()
{
    set("short", BLU"石坊"NOR);
    set("long", 
"一个巨大的牌坊横架在两片山壁之间，牌坊正上方刻着六个斗大的金字：\n"
"\n\t\t\t『"HIY"天下第一名刹"NOR"』\n\n"+
"字迹有些剥落，看上去年代颇为久远了。前方是一偏很大的广场，站满了前来\n"+
"进香的香客和一些江湖上的豪士。象征着少林寺的山门殿，就矗立在广场的另\n"+
"一侧。\n"
    );

	set("exits", ([
		"north" : __DIR__"guangchang",
		"south" : __DIR__"shijie11",
	]));

	set("outdoors", "shaolin");
  set("no_death", 1);
  set("no_get_from", 1); 
  set("no_sleep_room", 1);
  setup();
}
void init()
{
	object me,ob,obj;
	me = this_player();
	ob = this_object();
	if (!userp(me)) return;
  if(!me->query(QUESTDIR3+"bad") || !me->query_temp(QUESTDIR5+"zhangxing")||me->query_temp(QUESTDIR5+"zhenfa")||ob->query("busy"))
  {
   if(wizardp(me)) tell_object(me,HIR"测试。\n");
  	me->move("/d/shaolin/shifang");
    return;
  }
  if(!present("xiao feng",ob))
  {
  	obj=new("/d/shaolin/npc/tlbb_npc");
  	obj->set("party","gb");
  	obj->set("fight_id",me->query("id"));
  	obj->move(ob);
  	obj->kill_ob(me);
  }
  if(!present("wuming laoseng",ob))
  {
  	obj=new("/d/shaolin/npc/tlbb_npc");
  	obj->set("party","sl");
  	obj->set("fight_id",me->query("id"));
  	obj->move(ob);
  	obj->kill_ob(me);
  }
  ob->set("busy",me->query("id"));
  remove_call_out("check");
  remove_call_out("busy_pass");
  call_out("busy_pass",600); 
  call_out("check",1,me);
}

void pass_busy()
{
	object me,ob = this_object();
  if(ob->query("busy"))
  {
	  if(userp(me = present(ob->query("busy"),ob)) ) 
	  {
       if(!me->query(QUESTDIR3+"bad") || !me->query_temp(QUESTDIR5+"zhangxing"))
       {
  	     me->move("/d/shaolin/shifang");
         return;
       }      
	  }
             ob->delete("busy");
	}
	return;
}
void check(object me)
{
        object ob;
	if(!me || !living(me)||!present(me,this_object())||me->query("qi")<=1||me->query("jing")<=1)  
	{
		remove_call_out("check");
		if((ob=present("xiao feng",this_object())))
		{
	  	 message_vision(HIW"\n$N冷笑一声，一脸高傲的神态道：“有谁敢小看丐帮绝技。”\n"NOR, ob);
       destruct(ob);
    }
		if((ob=present("wuming laoseng",this_object())))
		{
	  	 message_vision(HIW"\n$N缓缓地道了声佛号。\n"NOR, ob);
       destruct(ob);
    }
    if(userp(me))
    { 
    	if(present(me,this_object()))
    	{
       	me->remove_all_killer();   	
    		me->reincarnate();
	  	  message_vision(HIW"\n突然一道神光笼罩着$N，$N的精气神竟然全部恢复了！\n"NOR, me);
        me->move("/d/shaolin/shifang");
    		tell_object(me,HIR"\n还是乖乖呆在少林潜修佛法算了！\n"NOR);
    		message_vision("$N急急忙忙地来到了"+environment(me)->query("short")+"。\n", me);
    	}
   	  me->delete_temp(QUESTDIR5+"zhenfa");
      log_file("quest/TLBB", sprintf("%s(%s)复兴天下最后一战失败。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );                  
    }
   	remove_call_out("busy_pass");
    this_object()->delete("busy");
	  return;
	}
	if (!present("xiao feng",this_object())&&!present("wuming laoseng",this_object()))
	{
		  remove_call_out("check");
		  me->remove_all_killer(); 

    	me->reincarnate();
	  	message_vision(HIW"\n突然一道神光笼罩着$N，$N的精气神竟然全部恢复了！\n\n"NOR, me);
		me->move("/d/shaolin/shifang");
		message_vision("$N急急忙忙地来到了"+environment(me)->query("short")+"。\n", me);
		me->set_temp(QUESTDIR5+"zhenfa",1);
		this_object()->delete("busy");
		log_file("quest/TLBB", sprintf("%s(%s)复兴天下最后一战成功。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );                  
    	return;
	}
  call_out("check",1,me);
}
int valid_leave(object me, string dir)
{
   return notify_fail(HIR"你无法离开这里。\n"NOR);
}
