#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西单北大街");
        set("long", @LONG
这里是北京城的西单北大街，宽阔的大道向南北走向延伸。街道
上的行人接踵而至，市井的喧哗声、官兵的马蹄声以及小商小贩的吆
喝声不断，鱼龙混杂其中，很是热闹。西边的街道通西城门。
LONG );
       set("exits", ([
                "east" : "/d/beijing/bei_2",
                "west" : "/d/beijing/ximenkou",
                "north" : "/d/beijing/bei_3",
                "south" : "/d/beijing/xi_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/youren" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}