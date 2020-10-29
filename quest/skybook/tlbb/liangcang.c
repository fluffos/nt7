inherit ROOM;
#include <ansi.h>
int do_jump(string arg);
int do_dianhuo(string arg);
void create()
{
    set("short", "后仓");
    set("long", @LONG
　　这是蒙古大军的囤粮之所，所谓兵马未动，粮草先行，
这里的粮食和草料堆积如山。一队队巡逻兵来回守卫，戒备
森严。
LONG);
	set("quest",1);
	set("exits", ([
		//"west" : __DIR__"sleep_room",
			"south" : __DIR__"zhongying",
        ]));
    setup();
}



int valid_leave(object me, string dir)
{
  if(present("liao bing",environment(me)))  return notify_fail("辽兵一把将你拦住：哪里跑！\n" );
  return ::valid_leave(me, dir);
}
void init()
{
  object me,obj;
  me = this_player();
  if(me->query_condition("killer"))
  {
   message_vision(HIC"\n突然$N似乎气血有些不顺，跟着一个趔趄倒了下去。\n"NOR,me); 
   tell_object(me,HIR"你突然感到一股力量吸引着你，瞬间你失去知觉。\n"NOR);
   tell_room(environment(me),HIR"\n只见，地上突然出现一个裂洞，"+ me->name()+ "一头扎了下去，瞬间消失。\n"NOR, ({}));
   me->move(__DIR__"shanlu1"); 
   tell_room(environment(me), HIR"\n半空中，似乎一个人掉了下来，你定眼一看竟然是"+ me->name()+ "。\n"NOR, ({}));
   me->unconcious();
   return;
  }
  add_action("do_jump", ({"jump","tiao"}));
  if(!me->query("quest/天龙八部/大辽救援篇/start")) return;
  if(me->query("quest/天龙八部/大辽救援篇/over")) return; 
  if(!me->query_temp("quest/天龙八部/大辽救援篇/godaliao")) return; 
  

  obj=new(__DIR__"npc/liaobing");
  obj->set("teamleader",1);
  obj->set("fight_id",me->query("id"));
  obj->move(environment(me)); 
  add_action("do_dianhuo", ({"dianhuo","burn"}));
}
int do_jump(string arg)
{
	object me;
	me = this_player();
	message_vision(HIC"$N看准了墙边一堆粮草，一跃而上，顺势在粮草轻轻一点，身子又飘出许尺。\n"NOR, me);
	me->move("/d/xingxiu/daliao/shulin");
	message_vision(HIC"$N一跃而起，环顾四周，这里竟然就是辽营的门前那片树林。\n"NOR, me);
	me->start_busy(1);
	return 1;
} 
int do_dianhuo(string arg)
{
	object me, ob,*obj;
	int i;
	me = this_player();
	ob = this_object();
	if (!me) return 0;
	if(!me->query_temp("quest/天龙八部/大辽救援篇/godaliao")) return 0; 
	if (present("liao bing", ob))
		return notify_fail("辽兵就在这里，先解决掉辽兵再说。\n");
	if (me->is_busy() || !arg )
		return notify_fail("你等等想好了烧什么再说。\n");    
	if (arg!="liang cao" && arg!="liangcao" && arg!="cao" )
		return notify_fail("你等等想好了烧什么再说。\n"); 
	if(me->query_temp("quest/天龙八部/大辽救援篇/dianhuo"))
		return notify_fail(HIR"火势已经上来，赶快离开这里去搭救萧峰。\n"NOR);    

	//只能一个人做
	obj = users();
	i = sizeof(obj);
	while(i--) {
		if ( obj[i]->query_temp("quest/天龙八部/大辽救援篇/dianhuo") && obj[i]!=me) 
		{
			me->delete_temp("quest/天龙八部");
			me->delete_temp("quest/busy");//任务冲突标志取消
			me->delete("quest/天龙八部/time");
			me->delete("quest/天龙八部/combat_exp");
			me->move(__DIR__"shanlu1"); 
			tell_object(me,HIR"已经有"+obj[i]->query("name")+RANK_D->query_respect(obj[i]) +"点火营救去了，不需要你了。\n"NOR);
			log_file("quest/TLBB", sprintf("%s(%s)解救萧峰点火，但和%s(%s)冲突失败。经验：%d。\n", me->name(1),me->query("id"), obj[i]->name(1),obj[i]->query("id"), me->query("combat_exp")) ); 
			return 1;  
		}
	}
	message_vision(HIC"\n$N悄悄转到粮草阴处，点起一把火，迅速窜到另外一个角落，用契丹话大叫：“走水啦！走水啦！”。果然，营中立即一团混乱，\n"
		             +"$N只要见到没有辽兵的地方，就是一把火，霎时间烧起了七八个火头。\n"NOR, me);
	message_vision(HIY"\n$N忽见东边狼烟冲天而起，那正是辽兵追来的讯号。$N心头一凛，还是赶快离开，去营救萧峰得好。 \n\n"NOR, me);
	log_file("quest/TLBB", sprintf("%s(%s)大辽点火成功。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) ); 
	me->set_temp("quest/天龙八部/大辽救援篇/dianhuo",1);
	me->start_busy(1);
	return 1;
} 
