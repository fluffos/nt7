inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long", @LONG
这里是汝州城的北大街。南去是汝州城中心，北去是汝州城的北城
门，这里也没有什么店铺。
LONG
        );

        set("exits", ([
                "north" : __DIR__"beimen",
                "south" : __DIR__"ruzhou",
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
