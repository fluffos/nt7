#include <room.h>
inherit ROOM;

void create()
{
        set("short", "凡陛桥");
        set("long", @LONG
凡陛桥是一座桥横跨东西的天桥，桥上面人声鼎沸，正是卖杂货、
变把戏、跑江湖的闲杂人等聚居的所在。宽阔的大道向南北两头延伸。
向南方对直迈进可以到达北京城里的名胜天坛。北方是一块宽阔的空
地，那里便是热闹的长安街广场了。凡陛桥的东西两个方向分别连接
了京城的永内东街和虎坊路。
LONG );
        set("exits", ([
                "south" : "/d/beijing/tiantan_n",
                "north" : "/d/beijing/cagc_s",
                "east" : "/d/beijing/yong_1",
                "west" : "/d/beijing/fu_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/maiyi3" : 1,
                "/d/beijing/npc/xianren" : 2,
                "/d/beijing/npc/xiaofan" : 1,
                "/d/beijing/npc/old3" : 1,
                "/d/beijing/npc/boy2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}