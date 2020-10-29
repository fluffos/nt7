// Room: /d/jiaxing/njwest.c
// Last Modified by Lonely on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "牛家村口");
        set("long", @LONG
这是一座小村落的西村口。村子很小，笼罩在一片寂静中。南边隐
约可以看到一条大江。
LONG
        );
        set("no_clean_up", 0);
        set("outdoors","jiaxing");

        set("exits", ([
                "northwest": __DIR__"road2",
                "east"     : __DIR__"njroad1",
        ]) );

	set("coor/x", 1240);
	set("coor/y", -1820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}