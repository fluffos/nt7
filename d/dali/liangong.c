// liangong.c

inherit ROOM;

void create()
{
        set("short", "练武场");
        set("long", @LONG
这里是一个不太的院子，是锻炼武功的地方。段家虽然世代皇族，
但是和江湖却有着割不断的联系。因此段家子孙有无数武道高手，这
里就是他们练功的场地。东南就是王府内院，北面则通往另一个练武
场。
LONG );
        set("exits", ([
                "north" : "/d/dali/liangong2",
                "southeast" : "/d/dali/yongdao1",
        ]));
        set("objects", ([
                "/clone/npc/mu-ren": 4,
        ]));
	set("coor/x", -19111);
	set("coor/y", -6821);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}