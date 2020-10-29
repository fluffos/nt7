#include <room.h>
inherit ROOM;

void create()
{
        set("short", "客店");
        set("long", @LONG
这是一家规模很小的客店，店里的摆设也相当的陈旧和简陋。客
店的老板是一个老头，因为这间小店的成本小，老头也就没请其它人
帮忙，客店内外的一切都是由他在打理。客店的柜台上挂着一个牌子
(paizi)。
LONG );
       set("exits", ([
                "east" : "/d/beijing/caroad_w1",
        ]));
        set("item_desc", ([
                "paizi" : "牌子上歪歪斜斜的写着两个字：\n\n"
                        "                       客满！\n\n",
        ]));
        set("objects", ([
                "/d/beijing/npc/chenlaotou" : 1,
                "/d/beijing/npc/youren" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();

        replace_program(ROOM);
}