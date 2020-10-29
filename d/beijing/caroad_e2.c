#include <room.h>
inherit ROOM;

void create()
{
        set("short", "东长安街");
        set("long", @LONG
热闹的东长安大街是紫禁城的交通要道，宽阔的青石大道向东西
两头延伸，街道上行人不断，繁华的盛世景象不言而喻。在这里可以
远远望见西边那一堵堵高大厚实的古城墙，便是著名的天安门广场了。
北面是京城最为繁华热闹的王府井大街。从南边传来一股浓烈的烟草
气味，原来那里是一家烟草店。东边是一家杂货铺。
LONG );
       set("exits", ([
                "north" : "/d/beijing/wang_2",
                "south" : "/d/beijing/yancao",
                "east" : "/d/beijing/zahuo",
                "west" : "/d/beijing/caroad_e1",
        ]));
        set("objects", ([
                "/d/beijing/npc/old1" : 1,
                "/d/beijing/npc/hunhun" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2770);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}