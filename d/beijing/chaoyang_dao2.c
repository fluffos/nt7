#include <room.h>
inherit ROOM;

void create()
{
        set("short", "朝阳道");
        set("long", @LONG
你走在尘土飞扬的朝阳道上，道路两旁是整整齐齐的杨树林，不
时有两三骑快马从身边飞驰而过，扬起一路尘埃。东边就是朝阳门了，
西边不远处是繁华的王府井大街，人声鼎沸，十分热闹。
LONG );
       set("exits", ([
                "west" : "/d/beijing/chaoyang_dao1",
                "east" : "/d/beijing/chaoyangmen",
        ]));
        set("objects", ([
                "/kungfu/class/hu/pingsi" : 1,
                "/d/beijing/npc/tiaofu" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2750);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}