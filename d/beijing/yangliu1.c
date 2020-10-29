#include <room.h>
inherit ROOM;

void create()
{
        set("short", "杨柳胡同");
        set("long", @LONG
这里是杨柳胡同的胡同口，深深的巷道朝着南边曲折的延伸下去，
旁晚时分，胡同口不远的西边炊烟渺渺，似是居住着几户人家。只见
北方尘土飞扬，马蹄声和吆喝声相互穿插，那里便是贯穿京城的长安
大街。
LONG );
       set("exits", ([
                "north" : "/d/beijing/caroad_w1",
                "south" : "/d/beijing/yangliu2",
                "west" : "/d/beijing/minju_y",
        ]));
        set("objects", ([
                "/d/beijing/npc/old1" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}