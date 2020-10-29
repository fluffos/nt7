inherit ROOM;

void create()
{
        set("short", "田埂小道");
        set("long", @LONG
这是一条向东的田间小道，两旁是一片片绿油油的水田和悠闲的
牧童。
LONG);
        set("exits", ([
                "west" : __DIR__"cunkou",
                "east" : __DIR__"road",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");
        set("no_pk", 1);
	setup();

        replace_program(ROOM);
}