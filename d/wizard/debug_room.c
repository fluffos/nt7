// /d/wizard/guest_room.c

#include <ansi.h>
#include <room.h>
#include <transmsg.h>
inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", HIM "试剑亭" NOR);
        set("long", @LONG
这里是天神用来调试程序的地方。
LONG );

        set("exits", ([
                "east": __DIR__"wizard_room",
                      "west"  : "/u/redl/modaotang2", 
        ]));


        set("coor/x", 9990);
        set("coor/y", 10000);
        set("coor/z", 10000);
        setup();
}







