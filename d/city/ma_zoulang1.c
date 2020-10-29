inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
这是马庄内的一条木制的走廊，红漆地面很是光滑。整个
走廊被打整得一尘不染。你不时能够看到几个丐帮的弟子在此
走动，忙碌个不停。
LONG);
        set("region", "yangzhou");
        set("exits", ([
                "north"  : __DIR__"ma_zhengting",
                "south"  : __DIR__"ma_zoulang2",
        ]));
        set("objects", ([
                "/d/gaibang/npc/1dai" : 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", 30);
	set("coor/y", -50);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}