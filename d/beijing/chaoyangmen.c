#include <room.h>
inherit ROOM;

void create()
{
        set("short", "朝阳门");
        set("long", @LONG
这里就是京城的朝阳门了，城墙上刻着『朝阳门』三个大字。向
西可以通往京城最热闹王府井大街。这里人来车往，是进出京城的要
道，城门两旁站满了官兵，盘查十分严密。一条宽阔的大道沿着东西
走向延伸，从这里出城到达京城的东郊。
LONG );
       set("exits", ([
              "east" : "/d/beijing/road1",
                "west" : "/d/beijing/chaoyang_dao2",
                "south" : __DIR__"matou",
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
        replace_program(ROOM);
}