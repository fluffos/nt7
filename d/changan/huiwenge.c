//Room: huiwenge.c

#include <ansi.h>

inherit ROOM;

void create ()
{
        set ("short", "汇文阁");
        set("long", @LONG
这是一家书局。大堂里摆了一排排的书柜，书架上整整齐齐地放
着一些卷轴，堂内还悬挂着几盆花花草草，红绿相间，疏密有致，令
人赏心悦目。进来就可以看到一额横匾：[1；34m         书山有径勤为路 
        学海无涯苦做舟[2；37；0m
LONG );

        set("exits", 
        ([ //sizeof() == 1
                "west" : "/d/changan/yongtai-dadao3",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/shuchi" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10750);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}