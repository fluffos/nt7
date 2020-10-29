#include <room.h>
inherit ROOM;

void create()
{
        set("short", "操练房");
        set("long", @LONG
这是二楼操练房上，四面八方都是打斗声，武当弟子来去匆匆，
都在忙着操练。
LONG );
        set("exits", ([
                "south" : __DIR__"caolian1",
                "north" : __DIR__"caolian2",
                "west" : __DIR__"caolian3",
                "eastdown"  : __DIR__"xilang"
        ]));
        set("objects", ([
                CLASS_D("wudang") + "/yin" : 1
        ]));
        set("coor/x", -390);
        set("coor/y", -300);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}