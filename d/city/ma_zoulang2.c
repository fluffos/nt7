inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
这是马庄内的一条木制的走廊，红漆地面很是光滑。整个
走廊被打整得一尘不染。你不时能够看到几个丐帮的弟子在此
走动，忙碌个不停。往北是个练武场。
LONG);
        set("region", "yangzhou");
        set("exits", ([
                "south"  : __DIR__"ma_lianwu1",
                "north"  : __DIR__"ma_zoulang1",
        ]));
        set("objects", ([
                "/d/gaibang/npc/2dai" : 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", 30);
	set("coor/y", -60);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}