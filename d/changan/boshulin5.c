// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short", "柏树林");
        set("long", @LONG
这里是一片枝繁叶茂的柏树林，花草长得便地都是，看着这原始
的密林，你似乎迷失了方向。
LONG
        );
        set("outdoors", "changan");
        set("exits", ([ /* sizeof() == 8 */
                "southwest" : __DIR__"boshulin5",
                "south" : __DIR__"boshulin5",
                "east" : __DIR__"boshulin6",
                "southeast" : __DIR__"boshulin5",
                "west" : __DIR__"boshulin5",
                "northwest" : __DIR__"boshulin5",
                "north" : __DIR__"boshulin4",
                "northeast" : __DIR__"boshulin5",
        ]));

        set("coor/x", -10650);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

