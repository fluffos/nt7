#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "永定门");
        set("long", @LONG
这里是是紫禁城永定门，高大的城门正上方刻着『永定门』三个
大字，厚实坚固的古城墙高高耸立着。城门两旁整齐的站着几个卫兵，
仔细的监守着这里。每天都有许多人经过这里出入京城。出了永定门，
一条笔直的大官道向南北两边延伸。南边的官道上人来车往，尘土飞
扬。北方则是通往京城的中心。
LONG );
        set("exits", ([
                "north" : "/d/beijing/yongdingdao",
                "south" : "/d/beijing/road5",
        ]));
        set("objects", ([
                "/d/beijing/npc/ducha" : 1,
                "/d/beijing/npc/bing1" : 2,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7610);
	set("coor/z", 0);
	setup();
}
