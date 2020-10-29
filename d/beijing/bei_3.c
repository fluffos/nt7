#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西单北大街");
        set("long", @LONG
这里是北京城的西单北大街，宽阔的大道向南北走向延伸。街道
上的行人接踵而至，市井的喧哗声、官兵的马蹄声以及小商小贩的吆
喝声不断，鱼龙混杂其中，很是热闹。西边是热闹的北街菜市，北方
就是西四北大街了。
LONG );
       set("exits", ([
                "east" : "/d/beijing/bei_4",
                "west" : "/d/beijing/caishi",
                "north" : "/d/beijing/shi_1",
                "south" : "/d/beijing/bei_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/girl3" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}