#include <room.h>
inherit ROOM;

void create()
{
        set("short", "四合院");
        set("long", @LONG
四合院是北京民居的典型，杨柳胡同中的这个四合院看来已经过
了一段很长久的历史了。四合院的大门破旧不堪，大门原本漆着的颜
色已无法辨认，门上还贴着一幅残破的对子，字迹模糊不清，猜想也
就无非是些『万事如意』什么的。你刚跨进四合院的大门，院内的居
民用奇怪的眼神上下打量着你，没事还是趁早离开吧。
LONG );
       set("exits", ([
                "east" : "/d/beijing/yangliu1",
        ]));
        set("objects", ([
                "/d/beijing/npc/jumin1" : 1,
               "/clone/npc/walker"  : 1, 
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}