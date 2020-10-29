#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西厢房");
        set("long", @LONG
这里是康亲王府的左边的一个厢房，是供王府的客人居住的。这
里站着一个身材瘦高的武师，两手别在腰后，似乎有一身好武功。
LONG );
        set("exits", ([
                "east" : "/d/beijing/kangfu_zoulang2",
        ]));

        set("objects", ([
                "/d/beijing/npc/qiyuankai" : 1,
        ]));

        set("sleep_room", "1");
        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}