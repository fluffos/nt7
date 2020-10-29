inherit ROOM;

void create()
{
        set("short", "南大街");
        set("long", @LONG
这里是汝州城的南大街。北去是汝州城中心，东面是红娘庄，西面
也没有什么店铺，南面是汝州的南城门。
LONG
        );

        set("exits", ([
                "north" : __DIR__"ruzhou",
                "south" : __DIR__"nanmen",
                "east"  : __DIR__"hong-damen",
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
