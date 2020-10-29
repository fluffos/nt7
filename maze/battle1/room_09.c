// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"山道"NOR);
        set("long", @LONG
这里是一条陡峭的山道，通望险峻的山峰。这里地势险要，真是一关把道，万夫莫行。
LONG
    );
        set("exits", ([
                "west"    : __DIR__"room_07",
                "up"      : __DIR__"etower1",
                "east"    : __DIR__"egarden",
        ]));

        set("outdoors", "battle");
        setup();
}
