// senlin7.c
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "百木园");
        set("long", @LONG
这里是梅庄的百木园，你一走到这里，就象走到了一个连绵无尽
的小森林一样，这里无数的松树，柏树，白杨，还有很多叫不出来名
字的异种苗木，你走在其中，只想把这片树林尽情的欣赏一遍，永不
出去才好。
LONG );

        set("exits", ([
                "east" : __DIR__"senlin"+(random(8)+1),
                "south" : __DIR__"senlin"+(random(8)+1),
                "west" : __DIR__"senlin"+(random(8)+1),
                "north" : __DIR__"senlin"+(random(8)+1),
        ]));
        set("outdoors", "meizhuang");
        setup();
        replace_program(ROOM);
}
