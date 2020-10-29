#include <room.h>
inherit ROOM;

void create()
{
        set("short", "天龙寺斋堂");
        set("long", @LONG
这是天龙寺的斋堂。整个房间飘荡着香味，一些仆役在不停的忙
碌着，桌上有各式的素菜、素酒，边上一角放着好多刚摘回来的青菜，
你不由得舔舔嘴巴，好象听到你的肚子“咕咕咕”的叫了起来。
LONG);
        set("no_fight",1);
        set("exits", ([
                "west"  : __DIR__"chufang",
                "south"  : __DIR__"yz1",
                "north"  : __DIR__"zhonglou",
        ]));
set("objects",([
		__DIR__"obj/rice" : 1,
		__DIR__"obj/dawan" : 1,
		__DIR__"obj/qingcai" : 2,
	]));

	set("no_fight", 1);

        set("coor/x",-360);
  set("coor/y",-350);
   set("coor/z",20);
   setup();
}
