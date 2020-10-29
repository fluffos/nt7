// Room: /d/city/jiaowai7.c
// Jan. 8.1998 by Venus
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", "草地");
        set("long", @LONG
这是扬州郊外的一片芳草地，落英缤纷，蜂歌蝶舞，朝露夕光，
沁人心脾。真是踏青远足好时光。
LONG );
    set("exits", ([
        "east" : "/d/city/jiaowai6",
        "west" : "/d/city/nanmen",
    ]));
    set("no_clean_up", 0);
    set("outdoors", "yangzhou");
	set("coor/x", 10);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();
}