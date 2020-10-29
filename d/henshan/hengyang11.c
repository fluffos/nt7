inherit ROOM;

void create()
{
        set("short", "衡阳西街");
        set("long", @LONG
这里是衡阳城西街，这见路人匆匆向东而行，南边是有一个马厩，
北面是一家装饰很典雅的店铺，店铺入门处挂满了风铃。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "east"   : __DIR__"hengyang1",
                "west"   : __DIR__"hsroad4",
                "south"  : __DIR__"majiu",
                "north"  : __DIR__"lingyinge",
        ]));

	set("coor/x", -6910);
	set("coor/y", -5700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
