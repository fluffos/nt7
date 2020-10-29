// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create ()
{
        set ("short",GRN"北门"NOR);
        set ("long", @LONG
这里是武汉的北门。这里地处繁华地带。东南边就是码头。来来往
往有很多行人和商人，所以热闹得很。许多小商小贩推着车从这里走过，
叫卖着自己的商品。有几个官兵正在这里检查着来往的行人。
LONG);

        set("exits", ([
                "south":__DIR__"hzjie1",
        ]));
        set("objects",([
                "/d/city/npc/bing":2,
        ]));
        set("outdoors", "wuchang");

	set("coor/x", -5090);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}