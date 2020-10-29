// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short", "柏树林");
        set("long", @LONG
你眼前豁然开朗，终于走出了这片柏树林，在往东走是一片杂草
丛生的草地。
LONG
        );
        set("outdoors", "changan");
        set("exits", ([ /* sizeof() == 3 */
                "south" : __DIR__"boshulin9",
                "east" : __DIR__"caodi",
        ]));

        set("coor/x", -10630);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

