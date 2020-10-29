inherit ROOM;

void create()
{
        set("short", "后门");
        set("long", @LONG
这里是关帝庙的后门，朝望北去，不远处是一个小山坡。
LONG );
        set("exits", ([
                "south" : __DIR__"houdian",
                "northup" :__DIR__"xiaoshan",
        ]));

        set("coor/x", -7120);
	set("coor/y", -2020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}