// update by Lklv for new nanyang city 2001.10.11

#include <ansi.h>
inherit ROOM;
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"

void create()
{
	set("short", "断崖");
	set("long", @LONG
前面是一处十分陡峭的断崖，险峻异常，难以爬越。这里离黄河不远，黄
河流淌到这里，河床宽阔。黄色的河水在静静地向东流去，使人忘记它发
洪水时的狂威。
LONG
	);
           set("quest",1);
	set("outdoors", "黄河");
	set("exits", ([
		"north" : __DIR__"yidao4",
	]));
	setup();
}

void init()
{
  object me,obj;
  me = this_player();
  if (!me->query(QUESTDIR3+"start")) return;
  if (!me->query_temp(QUESTDIR3+"kill")) return;
  if (me->query(QUESTDIR3+"over")) return;
  if (!me->query_temp(QUESTDIR3+"help")) return;
  if(present("xiao feng", environment(me)))return;
  me->start_busy(1);
  obj=new(__DIR__"npc/xiaofeng");
  obj->set("qi", obj->query("max_qi")/3);
  obj->set("eff_qi", obj->query("max_qi")/3);
  obj->set("jing", obj->query("max_jing"));
  obj->set("eff_jing", obj->query("max_jing"));
  obj->add("neili", obj->query("max_neili")*2);
  obj->set("jingli", obj->query("max_jingli"));
  if(obj->is_busy()) obj->start_busy(-1);	  
  if(!present("xiao feng", environment(me)))
  {
      obj->move(environment(me));
  }
}
int valid_leave(object me, string dir)
{
   object obj;
   if(obj=present("xiao feng", environment(me)))
   {
	   message_vision(HIY"\n$N点了点头道：“$n既然要走了，我也离开这里了，我先找一个地方疗伤再说。”\n" NOR, obj,me); 
       message_vision(HIY"\n$N微一凝神，运起混天气功，全身骨节发出一阵爆豆般的声响！\n" NOR, obj); 
	   message_vision(HIY"\n$N向$n招了招手，道：“等我伤势痊愈，我就会去找你的。”\n" NOR, obj,me); 
	   message_vision(HIY"\n$N跳下断崖，一转眼不见踪影了。\n" NOR, obj); 
       destruct(obj);
   }
   return ::valid_leave(me, dir);
}

