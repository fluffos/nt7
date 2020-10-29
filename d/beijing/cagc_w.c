#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西长安广场");
        set("long", @LONG
这里是天安门左边的西长安街广场，宽阔的长安大街向东西两头
延伸，这里京城里最热闹繁华的地段，既是交通要道，也是京城百姓
们的聚点， 广场上车水马龙，热闹非凡。小贩们沿街叫卖着自己的货
物。一些游手好闲的人常常在这里溜溜达达。这里可以望见东边高大
厚实的古城墙，那里便是天安门广场了。西边则是宽阔的西长安大街。
LONG );
       set("exits", ([
                "west" : "/d/beijing/caroad_w2",
                "east" : "/d/beijing/tiananmen",
                "north" : "/d/beihai/ximen",
        ]));
        set("objects", ([
                "/d/beijing/npc/girl4" : 1,
                "/d/beijing/npc/girl2" : 1,
                "/d/beijing/npc/shusheng2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}