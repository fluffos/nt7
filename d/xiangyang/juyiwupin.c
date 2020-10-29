// Room: /d/xiangyang/juyiwupin.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;

void create()
{
        set("short", "物品房");
        set("long", @LONG
这是聚义馆的堆放各种各样物品的房间。郭靖的二弟子武修文正
在这儿负责向有任务的新手分发各种物品。
LONG );
        set("exits", ([
                "northwest" : __DIR__"juyihuayuan",
        ]));
        set("objects", ([
                __DIR__"npc/wuxiuwen" : 1,
        ]));
        set("coor/x", -7830);
	set("coor/y", -810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
