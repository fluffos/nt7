// Room in 高丽
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","渔船");
        set("long", @LONG
渔船都连在一齐，而且都几乎是一模一样的，看得你头晕眼花。忽
然一个暗浪涌来，你一个不稳，‘啊。。。’，你几乎掉下了海去。
LONG
        );
        set("exits", ([
        "north" : __FILE__,
        "west" : __FILE__,
        "south" : __DIR__"yuchuan",
        "northwest" : __DIR__"yucun",
        ]));
        setup();
        replace_program(ROOM);
}

