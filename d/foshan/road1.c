inherit ROOM;

void create()
{
        set("short", "小道");
        set("long", @LONG
这里是一条林间小道，在树丛中蜿蜒。这里向东行进可到达广西。
向西北走就是大理国的地界了。
LONG );
        set("objects", ([
                __DIR__"obj/shikuai": 1,
        ]));

        set("outdoors", "foshan");
        set("exits", ([
	    "southwest" : "/d/dali/road5",
                "east"      : __DIR__"road2",
        ]));
	set("coor/x", -6670);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}