// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "花园");
        set ("long", @LONG
这是万家的后园，堆置了筛子、锄头、石臼、风扇之类杂物。在一
张小几放着一座香炉，香炉中插着三枝点燃了的线香。几前有个人跪着
向天磕头，不知祈着什么愿心。
LONG);
        set("outdoors", "jingzhou");
        set("region", "jingzhou");
        set("exits", ([
                "south" : __DIR__"wan_ketang",
                "east"  : __DIR__"wan_citang",
        ]));
        set("objects", ([
                __DIR__"npc/kongxincai"    : 1,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}