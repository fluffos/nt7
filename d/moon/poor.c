// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "泻玉泉");
	set("long", @LONG
扬花飘落，小荷初生。莺啼红树，蝶舞其间。仔细观看水池中建
一假山，上书泻玉二字，一眼活泉从假山上流过，一直向西延伸。
泉水流过山石，丁冬声竟似琴音。阳光虽烈，此处却清幽异常，
可见其建筑的独具匠心。
LONG	);
	set("exits", ([ 
  "east" : __DIR__"froom1",
]));
        set("objects",([
			__DIR__"obj/poor" : 1,
       	]) );
	set("coor/x",-40);
	set("coor/y",1150);
	set("coor/z",40);
	setup();
}
