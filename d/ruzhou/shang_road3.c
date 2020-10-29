inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
小镇旁的一条小路，因为平时过往之人不多的缘故，周围都
已长满了杂草。远远的向西望去，似乎有一座大宅。
LONG);
        set("exits", ([
                //"west"  : __DIR__"shang_road2",
                "west"  : __DIR__"xiaozheng",
                "north"  : __DIR__"shang_men",
        ]));
        set("outdoors", "ruzhou");
	set("coor/x", -6750);
	set("coor/y", 1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}