#include <room.h>
inherit ROOM;

void create()
{
	set("short", "天龙寺斋堂");
        set("long", @LONG
这是天龙寺的斋堂。整个房间飘荡着香味，一些仆役在不停的忙
着，边上一角放着好多刚摘回来的青菜，你不由得舔舔嘴巴，好象听
到你的肚子“咕咕咕”的叫了起来。
LONG);
        set("exits", ([
		"east"  : __DIR__"dmg",
	]));
        setup();
}

