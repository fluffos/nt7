#include <room.h>
inherit ROOM;

void create()
{
        set("short", "大院");
        set("long", @LONG
一个杂草丛生的四合院院子，大院北边是一条黑漆漆的胡同，四
周是几间房屋，房屋也不怎么破旧。院中横七竖八的倒着一些石锁、
铁环等寻常百姓健身用的器材。一个道人站在大院的正中，虎视耽耽
的盯着你。
LONG );
       set("exits", ([
                "north" : "/d/beijing/qingmu_men",
                "south" : "/d/beijing/qingmu_fang2",
                "east" : "/d/beijing/qingmu_fang1",
                "west" : "/d/beijing/qingmu_fang3",
        ]));
        set("objects", ([
                CLASS_D("yunlong") + "/xuanzhen" : 1
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7620);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}