inherit ROOM;

void create()
{
        set("short", "林间道");
        set("long", @LONG
这里是一条林间小道，在树丛中蜿蜒。岭南山林茂密，多产毒虫，
所以路人经过此地都是非常的小心。
LONG );
        set("outdoors", "foshan");
        set("objects", ([
                "/d/foshan/npc/bee": 1,
        ]));
        set("exits", ([
                "west"      : __DIR__"road2",
                "northeast" : __DIR__"road4",
        ]));
	set("coor/x", -6650);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}