// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIM"山道"NOR);
        set("long", @LONG
这里是一条陡峭的山道，通望险峻的山峰。这里地势险要，真是一关把道，万夫莫行。
LONG
    );
        set("exits", ([
                "northwest"     : __DIR__"room_15",
                "east"      : __DIR__"room_06",
                "south"     : __DIR__"room_17",
        ]));
        set("outdoors", "battle");
        setup();
}
