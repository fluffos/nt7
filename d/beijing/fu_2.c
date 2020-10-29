#include <room.h>
inherit ROOM;

void create()
{
        set("short", "虎坊路");
        set("long", @LONG
这里是京城的虎坊路，它西接凡陛桥。只要你身上有两钱儿，在
这里就会受到热情的招呼。任何你不知道的事，在这里打听一下，都
可以知道个八九不离十。北边邻街处有一家不大的客栈。南边是一座
巨大的宅院，像是某个达官贵人居住的场所。
LONG );
        set("exits", ([
                "south" : "/d/beijing/hai_men",
                "north" : "/d/beijing/fukedian",
                "east" : "/d/beijing/tianqiao",
                "west" : "/d/beijing/fu_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/haoke1" : 1,
                "/d/beijing/npc/girl2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}