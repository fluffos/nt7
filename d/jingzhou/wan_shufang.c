// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "书房");
        set ("long", @LONG
这是万老爷子的书房。摆设简单整洁。左首一堵白墙特别惹眼。
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "south" : __DIR__"wan_xilou",
        ]));

        set("no_clean_up", 0);
        set("coor/x", -7120);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}