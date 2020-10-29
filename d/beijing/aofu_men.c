inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","鳌府大门");
        set("long", @LONG
一座富丽堂皇的大宅院出现在你的眼前，两头高大的石狮子镇住
了大门两侧。门额上悬挂一方横匾，写着‘满洲第一勇士鳌狠府’几
个大字，门外有官兵把守，戒备森严。门上挂着两个灯笼，赫然写着
『鳌』字。这里就是当朝第一大臣，被御封为『满洲第一勇士』的鳌
狠的府邸。
LONG );
        set("exits", ([
                "north" : "/d/beijing/aofu_zoulang1",
                "south" : "/d/beijing/di_4",
        ]));
        set("objects", ([
                 "/d/beijing/npc/shi_a" : 2,
        ]));
	set("coor/x", -2820);
	set("coor/y", 7740);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (objectp(present("shi wei", environment(me))) && dir == "north")
                return notify_fail("鳌府侍卫一把拦住你，朗声喝道：王府要地，怎由闲杂人等随便进出。\n\n");
        return ::valid_leave(me, dir);
}