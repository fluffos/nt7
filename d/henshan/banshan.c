inherit ROOM;

void create()
{
        set("short", "半山亭");
        set("long", @LONG
终于到了半山亭。这里离到祝融峰无论高程还是行程，均恰好是
一半之径，路边小亭显然已极古久，但仍为过往客旅遮风避雨。
LONG );

        set("exits", ([
               "southdown"  : __DIR__"shanlu4",
               "northwest"    : __DIR__"shanlu002",
        ]));

        set("no_clean_up", 0);
        set("outdoors", "henshan");

	set("coor/x", -6910);
	set("coor/y", -5550);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}