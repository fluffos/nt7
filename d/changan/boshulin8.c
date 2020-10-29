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
                "southwest" : __DIR__"boshulin8",
                "south" : __DIR__"boshulin8",
                "east" : __DIR__"boshulin8",
                "southeast" : __DIR__"boshulin7",
                "west" : __DIR__"boshulin8",
                "northwest" : __DIR__"boshulin8",
                "north" : __DIR__"boshulin8",
                "northeast" : __DIR__"boshulin9",
        ]));

        set("coor/x", -10640);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

