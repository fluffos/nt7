#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地安门西街广场");
        set("long", @LONG
这里是地安门的西街的广场，地安门东西大街向两头延伸，这里
也京城里的繁华地段，是京城北边的交通要道。广场上热闹非凡，小
贩们沿街叫卖着自己的货物，其中也不乏夹杂着一些流氓混混。南边
是京城的特务机构西厂的所在地。东边就是地安门广场了。
LONG );
       set("exits", ([
                "north" : "/d/beijing/di_5",
                "south" : "/d/beijing/di_2",
                "east" : "/d/beijing/dianmen",
                "west" : "/d/beijing/di_3",
        ]));
        set("objects", ([
                "/d/beijing/npc/xianren" : 1,
                "/d/beijing/npc/hunhun" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}