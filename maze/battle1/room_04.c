// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG"山道"NOR);
        set("long", @LONG
这里是一条陡峭的山道，通望险峻的山峰。这里地势险要，真是一关把道，万夫莫行。
LONG
    );
        set("exits", ([
                "west" : __DIR__"wzoulan",
                "north" : __DIR__"room_03",
                "east"  : __DIR__"room_13",
        ]));
        set("outdoors", "battle");
        setup();
}
