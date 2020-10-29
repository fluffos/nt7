//yaofang.c

inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", GRN"药房"NOR);
	set("long", @LONG
这里是天龙寺的药房，房间里弥漫着浓浓的药香，房间内排满了装满各类
药材的大药柜，每个药柜都有上百个装药的抽屉贴满了各类药名。西边是一个
巨大红杉木柜，柜上贴着方丈印的封条。一位中年僧人正来回忙碌着指点众执役
僧称量药品，熬药煎汤。
LONG
	);
 set("exits", ([
             "north" : __DIR__"yaotai", 
        ]));

         set("objects",([
		 __DIR__"npc/liao-ming" : 1,
	]));

	
	set("coor/x",-310);
  set("coor/y",-330);
   set("coor/z",30);
   setup();
}



