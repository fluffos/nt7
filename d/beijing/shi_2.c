#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西四北大街");
        set("long", @LONG
这里是京城的西四北大街，青石铺砌道路贯通南北，街道上的行
人熙熙攘攘。西方一条宽阔的大官道上马蹄声不断，尘土飞扬。向南
通过西四北大街接西单北大街。
LONG );
       set("exits", ([
                "north" : "/d/beijing/shi_3",
                "south" : "/d/beijing/shi_1",
                "west" : "/d/beijing/guandao_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy1" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}