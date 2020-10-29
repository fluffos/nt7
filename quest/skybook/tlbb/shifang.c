// Room: /d/shaolin/shifang.c
// Date: YZC 96/01/19

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
	setup();
}

void init()
{
	object me = this_player();
	
	if ( me->query("sl_job")){
		me->add("job_time/少林", me->query("sl_job"));
		me->delete("sl_job");
	}
}
int valid_leave(object me, string dir)
{
  if(dir == "south" && me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && !me->query_temp(QUESTDIR5+"zhenfa"))
  {
   tell_object(me,HIC"\n你刚要准备离开少林寺。突然一南一北两个人影飞奔而来，竟然是少林无名僧和曾经一战的丐帮萧峰。\n"NOR); 
   me->move("/d/shaolin/shifang_copy");
   log_file("quest/TLBB", sprintf("%s(%s)复兴天下最后一战开始。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
   return notify_fail(HIR"看来这一战，实在难免了。\n"NOR);
  }
	return ::valid_leave(me, dir);
}
