inherit ROOM;

void create()
{
        set("short", "鳌府大院");
        set("long", @LONG
你走进大院，迎面是一个大花园，花园中假山水池，很是美观。
池中立着一块巨大无比的翡翠，显然是鳌狠搜刮来的宝物。水池的两
旁种满了花草，郁郁葱葱，树木枝叶茂密，遮盖了大半个院子，显得
阴森恐怖。北边一条长长的木制长廊，通往鳌府的大厅。
LONG );
        set("exits", ([
                "north" :  "/d/beijing/aofu_dating",
                "south" :  "/d/beijing/aofu_zoulang1",
        ]));
        set("objects", ([
                "/d/beijing/npc/yuanding" : 1,
        ]));

	set("coor/x", -2820);
	set("coor/y", 7760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}