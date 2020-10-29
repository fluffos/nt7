// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "柴房");
        set ("long", @LONG
这是万家堆放柴草的地方。
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "south"  : __DIR__"wan_donglou",
        ]));
        set("objects", ([
                __DIR__"npc/wukan"    : 1,
        ]));

        set("coor/x", -7100);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}