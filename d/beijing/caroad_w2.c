#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西长安街");
        set("long", @LONG
热闹的西长安大街是紫禁城的交通要道，宽阔的青石大道向东西
两头延伸，街道上行人不断，繁华的盛世景象不言而喻。在这里可以
远远望见东边那一堵堵高大厚实的古城墙，便是著名的天安门广场了。
从这里转北就是西单了，那也是京城里的繁华地段。南边茶铺里不时
传来一阵阵喧杂的吵闹声。
LONG );
       set("exits", ([
                "west" : "/d/beijing/caroad_w1",
                "east" : "/d/beijing/cagc_w",
                "north" : "/d/beijing/xi_2",
                "south" : "/d/beijing/gaosheng",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy2" : 1,
                "/d/beijing/npc/richman1" : 1,
                "/d/beijing/npc/shusheng1" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}