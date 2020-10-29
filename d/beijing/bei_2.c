#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西单北大街");
        set("long", @LONG
这里是北京城的西单北大街，宽阔的大道向南北走向延伸。街道
上的行人接踵而至，市井的喧哗声、官兵的马蹄声以及小商小贩的吆
喝声不断，鱼龙混杂其中，很是热闹。往西走的通西城门，东边是一
座富丽堂皇的建筑，门额上悬挂一方横匾，写着『康亲王府』四个大
字。
LONG );
       set("exits", ([
                "east" : "/d/beijing/kangfu_men",
                "west" : "/d/beijing/bei_1",
                "north" : "/d/beijing/bei_4",
                "south" : "/d/beijing/xi_2",
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}