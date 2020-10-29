#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西长安街");
        set("long", @LONG
热闹的西长安大街是紫禁城的交通要道，宽阔的青石大道向东西
两头延伸，街道上行人不断，繁华的盛世景象不言而喻。在这里可以
远远望见东边那一堵堵高大厚实的古城墙，便是著名的天安门广场了。
北面是繁华的西单，左边不远处有一家规模不大的客店。南面的街道
逐渐狭窄，便是杨柳胡同的胡同口了。
LONG );
       set("exits", ([
                "east" : "/d/beijing/caroad_w2",
                "west" : "/d/beijing/kedian",
                "north" : "/d/beijing/xi_1",
                "south" : "/d/beijing/yangliu1",
        ]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
                "/d/beijing/npc/haoke1" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}