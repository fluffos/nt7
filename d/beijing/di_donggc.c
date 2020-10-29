#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地安门东街广场");
        set("long", @LONG
这里是地安门的东街的广场，地安门东西大街向两头延伸，这里
也京城里的繁华地段，是京城北边的交通要道。广场上热闹非凡，小
贩们沿街叫卖着自己的货物，其中也不乏夹杂着一些流氓混混。南边
是京城的特务机构东厂的所在地。西边是地安门广场，东边接京城著
名的王府井大街。
LONG );
       set("exits", ([
                "north" : "/d/beijing/dong_2",
                "south" : "/d/beijing/dong_1",
                "east" : "/d/beijing/wang_9",
                "west" : "/d/beijing/dianmen",
        ]));
        set("objects", ([
                "/d/beijing/npc/liumang" : 1,
                "/d/beijing/npc/kid1" : 1,
                "/d/beijing/npc/girl2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}