inherit ROOM;

void create()
{
        set("short", "龙亭大殿");
        set("long", @LONG
龙亭大殿原先是帝王行宫，后宋亡之后，宫殿颓废，后人在此地
复建大殿，殿内珍宝林陈高檐直柱，令人叹为观止。集南北宫殿建筑
之大成。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"road5",
                  "west" : __DIR__"tinyuan",
        ]));

	set("coor/x", -5070);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}