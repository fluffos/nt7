inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","海澄公府");
        set("long", @LONG
你来到一所巨宅门前，巨宅的大门紧紧关闭着，门上挂着一块大
匾，匾上写着『海澄公府』四个大字，虽然和鹿鼎公府同是公爵府，
可是大小、派头却大不相同，大门匾额上那『海澄公府』四字是黑字，
一点也不起眼。
LONG );
        set("exits", ([
                "north" : "/d/beijing/fu_2",
                "south" : "/d/beijing/hai_dayuan",
        ]));

	set("coor/x", -2810);
	set("coor/y", 7640);
	set("coor/z", 0);
	setup();
}