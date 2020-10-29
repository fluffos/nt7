//Created by Redhat@Sjmud 2009/4/7
//updated by Zhuifeng@SJFY 2010/7/27

inherit ROOM;
#include <ansi.h>
#define QUESTDIR "quest/射雕英雄传/风雪惊变/"
void create()
{
	set("short", "杨家小屋");
	set("long", @LONG
这是一座十分清爽的民房，家具摆设一应俱全，只是都附着一层灰土。屋
子中间是一张小桌，桌上的杯碗还都没有撤去，看来主人去的很匆忙。墙上挂
着一杆短柄生了锈的铁枪(Tieqiang)。
LONG
	);

	set("item_desc", ([
		"tieqiang" : "一杆用旧了的铁枪，看起来原来应该有一对的，不知为何只剩了一杆。\n",
	]) );

	set("exits", ([
		"north" : __DIR__"houyuan.c",
	  "south" : __DIR__"qianyuan.c",
	]));

	setup();
}

void init()
{
  object me,obj;
  me = this_player();
  if (me->query(QUESTDIR+"start")
 		 &&!me->query_condition("killer")
		  &&!me->query(QUESTDIR+"over")
		  &&!me->query_temp(QUESTDIR+"have_kill")
     &&!me->query_temp(QUESTDIR+"kill"))
  {
     tell_object(me,HIC"杨铁心怒气填膺，开门走出，大声喝道：“我就是杨铁心！你们干甚么？”两名兵丁吓了一跳，丢下火把转身退开。”\n" 
                       "火光中一名武官拍马走近，叫道：“好，你是杨铁心，跟我见官去。拿下了！”四五名兵丁一拥而上。杨铁心倒转枪来，\n"NOR+
                    RED"一招“白虹经天”，把三名兵丁扫倒在地，又是一招“春雷震怒”，枪柄跳起一兵，惯入了人堆，喝道：“要拿人，先得说说我犯了甚么罪。”\n"NOR); 
     message_vision(HIR"\n金兵突然看见$N你冲进来，全体一愣，突然一个金兵甲说道：“敢挡大爷捉拿要犯，给我杀了。”\n"NOR, me);
     obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));      
     obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));        
     obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));    
     remove_call_out("killme");
     call_out("killme", 5, me);        
    }      
}
void killme(object me)
{
	object obj;
  if(!me) return;

  if (me->query(QUESTDIR+"start")
 		 &&!me->query_condition("killer")
 		  &&!me->query_temp(QUESTDIR+"have_kill")
     &&!me->query_temp(QUESTDIR+"kill"))
  {
     obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me)); 
     tell_object(me,HIG"\n\n你只感觉这金兵甲行事为何如此卑鄙，居然不分青红皂白杀人，不由火气暴涨，立刻对金兵发动攻击。\n"NOR); 
     obj->unconcious();
  }  
}
int valid_leave(object me, string dir)
{
       if (me->is_fighting())
                return notify_fail(RED"\n金兵大声喝道：哪里走。一把拦住你，你竟然无法离开。\n"NOR);
       if (present("jin bing",this_object()))
                return notify_fail(RED"\n金兵大声喝道：哪里走。一把拦住你，你竟然无法离开。\n"NOR);
   		if(me->query_condition("killer")) 
   		          return notify_fail(RED"\n怎么进来的？？这里等wiz吧。\n"NOR);
        return ::valid_leave(me, dir);
}

