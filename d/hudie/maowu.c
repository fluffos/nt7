// 茅屋 maowu.c
 
#include <ansi.h>

inherit ROOM;

void create() 
{ 
        set("short", "茅屋");
        set("long", @LONG
这里是一间简陋的茅屋，正中摆放着一张木桌，周围整齐地放着
几张凳子，一个小童正坐在那里打瞌睡，看到有人来了，赶忙热情地
迎了上来。西面很安静，东面一阵药气传了过来，北面一道帘子，不
知道是什么地方。
LONG );

        set("exits", ([
            "north" : __DIR__"caotang",
            "west" : __DIR__"xfang2",
            "south" : __DIR__"caojing",
            "east" : __DIR__"yaofang",
        ]));

        setup();
}