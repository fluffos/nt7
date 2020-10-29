// /u/cool/tls/wanfodong3.c
// cool 1998.2.13
#include <room.h>

inherit ROOM;

void create()
{
	set("short", "万佛洞内洞");
	set("long", @LONG
这里是万佛洞的内洞了，洞内显得较昏暗异常，你看不清什么东
西，洞内静静的，只听见自己的脚步声和心跳呼吸声，隐隐有个人面
对着墙壁坐着。这里没有什么明显的出口。
LONG);
	set("exits", ([
	       "south" : __DIR__"wfd2",
        ]));
      
        create_door("south", "石门", "north", DOOR_CLOSED);
	setup();
}


