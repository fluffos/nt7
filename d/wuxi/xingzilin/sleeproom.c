// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "山洞");
        set("long", @LONG
这是一个漆黑的大山洞，循呼呼大睡的鼾声望去，能看到洞里地上
横七竖八地摆放着几床臭草垫。
LONG    );

                set("objects", ([
                __DIR__"npc/beggar" : 1,
                ]));
        set("exits", ([
                "east" : __DIR__"road4",
        ]));

        set("sleep_room", 1);
                set("no_magic", 1);
        set("no_fight", 1);
        set("no_clean_up", 0);

        setup();
}

