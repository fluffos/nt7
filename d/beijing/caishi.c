#include <room.h>
inherit ROOM;

void create()
{
        set("short", "北街菜市");
        set("long", @LONG
这里是京城西单北大街西边的一个菜市，青石板铺砌着地面。街
的两边摆满了蔬菜摊和水果摊， 小贩门大声吆喝着，京城的百姓都是
从这儿把每天所需的食物购回， 做成一顿顿可口的佳肴。
LONG );
       set("exits", ([
                "east" : "/d/beijing/bei_3",
        ]));
        set("objects", ([
                "/d/beijing/npc/caifan" : 1,
                "/d/beijing/npc/jumin1" : 2,
              "/clone/npc/walker"  : 1, 
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}