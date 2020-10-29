inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
这是一条宽阔的青石板街道，向东西两头延伸。这里行人稀少，
静悄悄地很是冷清。东边是一个热闹的广场。南边是荆州府衙。北边
是一座豪华大院，那就是万门万府了。
LONG );
        set("outdoors", "jingzhou");

        set("exits", ([
                "east" : __DIR__"guangchang",
                "south" : __DIR__"jzyamen",
                "west" : __DIR__"xidajie2",
                "north" : __DIR__"wan_damen",
        ]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
        ]));
        set("coor/x", -7110);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}