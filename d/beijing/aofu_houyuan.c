inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","鳌府后院");
        set("long", @LONG
这里是鳌府的后院，中心是一个大花园。西边一条长廊走道直通
往鳌狠的书房。北边是鳌狠私设的牢房，牢门由几个鳌府的侍卫把守
着。
LONG );
        set("exits", ([
                "north" :  "/d/beijing/aofu_naofang",
                "west" :  "/d/beijing/aofu_zoulang3",
                "south" :  "/d/beijing/aofu_zoulang2",
        ]));
        set("objects", ([
                "/d/beijing/npc/shi_a" : 2,
        ]));
	set("coor/x", -2820);
	set("coor/y", 7790);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (objectp(present("shi wei", environment(me))) && dir == "north")
                return notify_fail("鳌府侍卫拦住你道：没有王爷的吩咐，谁也不能进去。\n\n");
        return ::valid_leave(me, dir);
}