// Room : /d/dali/huanggs.c 黄果树瀑布

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "黄果树瀑布");
        set("long", @LONG
这儿是大理闻名于天下的黄果树瀑布，河流纵横交错，瀑布成群，
洞穴成串，峰峦叠翠，植被奇特，呈现出层次丰富的喀斯特山水旖旎
风光。
LONG );
        set("outdoors", "dali");

        set("exits", ([
                "east" : __DIR__"feilihusouth",
        ]));
	set("coor/x", -19140);
	set("coor/y", -6970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}