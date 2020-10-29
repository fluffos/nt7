inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
这是成德殿内的一条木制的走廊，红漆地面很是光滑，整个走廊
被打整得一尘不染。你不时能够看到几个成德殿的侍女在此走动，忙
碌个不停。
LONG );
        set("exits", ([
                "north"  : __DIR__"huoting",
                "south"  : __DIR__"chengdedian",
        ]));
        set("objects", ([
                __DIR__"npc/zish" : 1,
        ]));
        setup();
        replace_program(ROOM);
}