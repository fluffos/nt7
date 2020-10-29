// Room: /d/nanyang/jxzhuang.c
// Lklv Modify 2001.10.10
// Tangfeng@SJ 2004

#include <ansi.h>
inherit ROOM;
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"

void create()
{
        set("short", "聚贤庄大门");
        set("long",
"你走到一座高宅大院的门口，大门开着，门前左右有两个石狮子，四五级\n"
"青石台阶上是两扇钉满铜钉的大门。看得出这里是一大户人家的住所。门口正\n"
"中央高悬着一块黑底金字的大匾，匾上写有三个大字："YEL"【聚贤庄】"NOR"。\n"
        );
		set("quest",1);
		set("outdoors", "南阳");
		set("exits", ([
			"southwest" : __DIR__"xiaolu3",
				"north" : __DIR__"dating",
		]));

		set("objects",([
			__DIR__"npc/guanjia" : 1,
				__DIR__"npc/jiading" : 1,
		]));
        
		setup();
}
void init()
{
	object obj,me = this_player();
	if ( me->query(QUESTDIR3+"start")
		&& !me->query_temp(QUESTDIR3+"kill")
		&& !me->query(QUESTDIR3+"over")){
			me->start_busy(2);
			//玩家离开这里，离开算失败
			obj=new(__DIR__"npc/guanjia");
			if(!present("guan jia",this_object()))
				obj->move(this_object());
			obj=new(__DIR__"npc/jiading");
			if(!present("guan jia",this_object()))
				obj->move(this_object());		
		}
}
int valid_leave(object me, string dir)
{
   object room;
   if (!(room = find_object(__DIR__"dating")))
       room = load_object(__DIR__"dating");

   if(room && room->query("busy")&& dir == "north" )
     return notify_fail(HIR"你发现聚贤庄内似乎传来激烈的打斗之声，还是走为上策！\n"NOR);
   
   if (me->query(QUESTDIR3+"start") 
         && !me->query(QUESTDIR3+"over") 
         && dir == "north" 
         && present("guan jia", environment(me)))
     return notify_fail(HIR"管家冷笑一声道：这位"+RANK_D->query_respect(me) +"请回，这里不欢迎你！\n"NOR);
     if (me->query(QUESTDIR3+"start") 
         && !me->query(QUESTDIR3+"over") 
         && dir == "north" 
         && present("jia ding", environment(me)))
     return notify_fail(HIG"家丁冷笑一声道：这位"+RANK_D->query_respect(me) +"请回，这里不欢迎你！\n"NOR);

     if(dir == "north" &&(me->query_condition("killer")||	sizeof(filter_array(deep_inventory(me), (: userp :)))))
		 return notify_fail(HIY"突然从里面传来一阵冷笑道：这位"+RANK_D->query_respect(me) +"请回，这里不欢迎你！\n"NOR);
     return ::valid_leave(me, dir);
}
