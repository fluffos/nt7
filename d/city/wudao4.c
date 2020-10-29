// Room: /city/wudao4.c
// Date: Feb.28 1998 by Java

#include <ansi.h>

inherit "/d/city/underlt";

void create()
{
        set("short", "武道场");
        set("long", @LONG
这里是三面环山，只有北面有条出口的一坪山间平地。山坡山阵
阵松涛哗哗作响，山脚下的平地绿草如茵，中间架起了个擂台，四周
一溜过去搭着凉棚，棚中桌椅杯盆俱全。西面是少年组的比武场，东
面是青年组的比武场，南面是成年组的比武场。
LONG );
        set("outdoors", "city");
        set("exits", ([
                "north"       : "/d/city/ximenroad",
                "west"        : "/d/city/wudao1",
//                "east"        : "/d/city/wudao2",
//                "south"       : "/d/city/wudao3",
//               "up"  : "/d/sjszhuang/gate",
        ]));
        set("no_fight", 1);
	set("coor/x", -50);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
        "/clone/board/wudao_b"->foo();
        init_here();
        replace_program("/d/city/underlt");
}
