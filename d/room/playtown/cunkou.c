// by 山猫ADX @ snow 99-12-4

#include <ansi.h>
inherit ROOM;

void create ()
{
        set("short",  "村口");
        set("long",
"这里就是"HBRED WHT"『泥潭』"NOR+
"的玩家村。这里非常的安静，看来玩家们都在忙\n"
"着挖泥巴，真是累啊！\n"
);
        set("exits",  ([
                "north"  :  __DIR__"guandao8",
                "south"  :  __DIR__"road14",
        ]));
        set("outdoors",  1);
        setup();
        replace_program(ROOM);
}