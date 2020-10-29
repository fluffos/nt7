inherit ROOM;

void create()
{
        set("short", "荆州中心" );
        set("long", @LONG
这里是荆州的中心要十字路口，人来人往，很是热闹，南边住着
一些本城的富人，北边是官府，真是一个好地方啊。许多从四川来的
人都在此落脚，休息以后再赶路。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : __DIR__"dongdajie1",
                "west" : __DIR__"xidajie1",
                "north" : __DIR__"beidajie1",
                "south" : __DIR__"nandajie1",
        ]));
        set("objects", ([
                "/d/beijing/npc/haoke1" : 1,
                "/d/beijing/npc/maiyi1" : 1,
                "/d/beijing/npc/boy1" : 1,
                "/d/beijing/npc/old2" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -7100);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}