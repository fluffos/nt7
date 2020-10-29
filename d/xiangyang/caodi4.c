// Room: /d/xiangyang/caodi4.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "草地");
        set("long", @LONG
这是襄阳城外的草地。蒙古兵进犯以来，这里的百姓全进城了，
这里几十里都没了人烟。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "west"  : __DIR__"southgate2",
        ]));

        set("objects", ([
                CLASS_D("hu") + "/cheng" : 1,
        ]));

        set("coor/x", -7810);
	set("coor/y", -820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}