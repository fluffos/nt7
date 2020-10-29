// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "山庄大门");
	set("long", @LONG
这儿就是名震江湖的圆月山庄，山庄的大门是一座高大的飞檐建筑，
其气势恢弘非任何门派可以比拟。左右两只石狮遥相呼应，中间上方
悬挂着一方金匾;
[33m
   
                       圆 月 山 庄

[37m
LONG	);
	set("exits", ([ 
  "north" : __DIR__"bi",
  "southdown" : __DIR__"road3",
]));
        set("objects",([
			__DIR__"npc/guards2" : 2,
       	]) );
	set("coor/x",-30);
	set("coor/y",1070);
	set("coor/z",40);
	setup();
}
