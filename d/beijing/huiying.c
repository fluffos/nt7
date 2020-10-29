#include <room.h>
inherit ROOM;

void create()
{
        set("short", "汇英酒楼");
        set("long", @LONG
汇英酒楼在整个京城中，也算是小有名气的了。酒楼里面雕梁画
壁，装饰有如宫殿，你可以在这里打听到各地的风土人情。店小二里
里外外忙得不可开交，接待着南腔北调的客人。楼里桌椅洁净。座中
客人衣饰豪奢，十九是富商大贾。
LONG );
       set("exits", ([
                "north" : "/d/beijing/yong_1",
                "up" : "/d/beijing/huiyingup",
        ]));
        set("objects", ([
                "/d/beijing/npc/xiaoer2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7640);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}