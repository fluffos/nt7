#include <room.h>

inherit ROOM;
void create()
{
        set("short", "灵州西门");
        set("long", @LONG
这是西城门，城门正上方刻着几个西夏文字。城墙上贴着几张官府
告示。一条路往西通向城外玄冥峰。
LONG );
        set("exits", ([
                "west"      : "/d/xuanminggu/xiaolu1",
                "southeast" : __DIR__"xidajie",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6295);
        set("coor/y", 2935);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

