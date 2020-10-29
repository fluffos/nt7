inherit ROOM;

void create()
{
        set("short", "粮仓");
        set("long", @LONG
这里就是荆州粮仓了，地上堆着许多麻袋，大概装的是包谷大米
之类的粮食。
LONG );
        set("exits", ([
                "west" : __DIR__"lcmen",
        ]));

        set("coor/x", -7080);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}