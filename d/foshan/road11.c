inherit ROOM;

void create()
{
        set("short", "林间道");
        set("long", @LONG
这里是一条林间小道，在树丛中蜿蜒。岭南山林茂密，多产毒虫，
所以路人经过此地都是非常的小心。
LONG );
        set("objects", ([
                __DIR__"obj/shikuai": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "northeast" : __DIR__"road13",
                "southwest" : __DIR__"road10",
        ]));
	set("coor/x", -6500);
	set("coor/y", -9740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}