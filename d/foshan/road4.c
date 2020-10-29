inherit ROOM;

void create()
{
        set("short", "林间道");
        set("long", @LONG
这里是一条林间小道，在树丛中蜿蜒。岭南山林茂密，多产毒虫，
所以路人经过此地都是非常的小心。
LONG );
        set("objects", ([
                "/clone/beast/dushe": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "southwest" : __DIR__"road3",
                "southeast" : __DIR__"road5",
        ]));
	set("coor/x", -6640);
	set("coor/y", -9740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}