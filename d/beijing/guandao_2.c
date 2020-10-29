#include <room.h>
inherit ROOM;

void create()
{
        set("short", "大官道");
        set("long", @LONG
你走在一条尘土飞扬的大官道上。不时有两三骑快马从身边飞驰
而过，扬起一路尘埃。道路两旁是整整齐齐的杨树林。北方不远处就
是京城著名的名胜十三皇陵。
LONG );
       set("exits", ([
                "north" : "/d/beijing/huangling",
                "south" : "/d/beijing/guandao_1",
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}