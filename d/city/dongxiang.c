// Room: /city/dongxiang.c
// YZC 1995/12/04 

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "财主东厢");
        set("long", @LONG
这是一个昏暗的房间，窗户都被钉死。地上放着皮鞭、木棍等刑
具，显然这是财主私立公堂，折磨仆人、丫鬟的所在。一个丫鬟被绳
子绑着，浑身赤裸跪在地上哭哭啼啼，身上是一道道的伤口。
LONG );
	set("exits", ([
		"west" : "/d/city/houyuan",
	]));
	set("objects", ([
		"/d/city/npc/hongniang" : 1,
	]));
//	set("no_clean_up", 0);
        set("coor/x", -35);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
