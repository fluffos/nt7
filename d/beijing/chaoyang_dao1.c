#include <room.h>
inherit ROOM;

void create()
{
        set("short", "朝阳道");
        set("long", @LONG
你走在尘土飞扬的朝阳道上，道路两旁是整整齐齐的杨树林，不
时有两三骑快马从身边飞驰而过，扬起一路尘埃。东边不远处就是朝
阳门了，西边是繁华的王府井大街，人声鼎沸，十分热闹。
LONG );
       set("exits", ([
                "west" : "/d/beijing/wang_4",
                "east" : "/d/beijing/chaoyang_dao2",
        ]));
        set("objects", ([
                "/d/beijing/npc/tangzi" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2760);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}