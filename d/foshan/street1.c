inherit ROOM;

void create()
{
        set("short", "西镇街");
        set("long", @LONG
佛山镇街道平整。西面是镇西门，北面有一座北帝庙，建构宏伟，
好大一座神祠。
LONG );
        set("objects", ([
                __DIR__"npc/jiading": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "north" : __DIR__"beidimiao",
                "west"  : __DIR__"westgate",
                "east"  : __DIR__"street2",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -6590);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}