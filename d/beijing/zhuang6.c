#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "庄府大厅");
        set("long", @LONG
这是一间灵堂，堂上供了七八个牌位。看来一座灵堂上供的是一
家死人。一阵阴风吹过，蜡烛突然灭了。
LONG );
    set("exits", ([
        "west" : "/d/beijing/zhuang5",
    ]));
    set("objects", ([
        "/d/shenlong/npc/dizi": 1,
    ]));
    set("outdoors", "beijing");
    set("coor/x", 100);
        set("coor/y", 4730);
        set("coor/z", 0);
        setup();
    replace_program(ROOM); 
}