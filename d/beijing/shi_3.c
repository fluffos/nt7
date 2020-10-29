#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西四北大街");
        set("long", @LONG
这里是西四北大街的尽头，青石铺砌大道相当宽阔，街道上的行
人熙熙攘攘，车马穿流不息。东边接地西大街，转南则通过西四北大
街接京城的西单北大街。
LONG );
       set("exits", ([
                "east" : "/d/beijing/di_4",
                "south" : "/d/beijing/shi_2",
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}