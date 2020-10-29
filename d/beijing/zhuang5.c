#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "庄府大厅");
        set("long", @LONG
这是一间大厅，通往各个房间。东边的屋里有女子啼哭之声隐隐
传来。
LONG );
    set("exits", ([
        "east" : "/d/beijing/zhuang6",
        "west" : "/d/beijing/zhuang7",
        "north" : "/d/beijing/zhuang8",
        "south" : "/d/beijing/zhuang3",
    ]));
    set("objects", ([
        "/d/shenlong/npc/dizi": 2,
        "/d/shenlong/npc/zhang3": 1,
    ]));
    set("outdoors", "beijing");
    set("coor/x", 100);
        set("coor/y", 4720);
        set("coor/z", 0);
        setup();
    replace_program(ROOM); 
}