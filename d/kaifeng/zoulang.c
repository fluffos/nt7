inherit ROOM;

void create()
{
        set("short", "明廊");
        set("long", @LONG
明廊的地板离地三尺，两边原来都是菜园子，自从东角门外住了
帮泼皮之后，这几块地里再没出过菜。东面还是走廊西面有个小门通
向素斋厨房，阵阵香味就从门中飘了出来。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"chufang2",
                  "east" : __DIR__"zoulang2",
        ]));
        set("outdoors", "xiangguosi");

	set("coor/x", -5020);
	set("coor/y", 2210);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
