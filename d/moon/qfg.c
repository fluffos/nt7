// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "清风阁");
	set("long", @LONG
这里是圆月山庄的第二大建筑。古槐覆阴之下，红楼掩映，
上面彩纱宫灯，缀成了“清风阁”三字。四周的石栏，挂满许多
水晶玻璃的各色风灯，点得如银花雪浪。
LONG	);
	set("exits", ([ 
  "northup" : __DIR__"yyl",
  "southdown" : __DIR__"froom",
  "eastdown" : __DIR__"yqx",
  "westdown" : __DIR__"yst",
]));
       set("objects",([
			__DIR__"npc/guards2" : 2,
                        __DIR__"obj/deng" : 1, 
       	]) );
        set("valid_startroom", 1);
	set("coor/x",-30);
	set("coor/y",1130);
	set("coor/z",60);
	setup();
}
