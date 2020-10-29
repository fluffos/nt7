//shandao4.c                四川唐门—后山山道

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "山道");
        set("long",
"这里是通向山顶的小道。奇陡无比，一不小心就会摔下去，两边是高\n"
"耸入云的参天大树，越接近山顶温度越低了，你扣紧衣襟仍感到寒气逼人。\n"
);
        set("exits", ([
                        "northup" : __DIR__"shandao5",
                        "southwest" : __DIR__"shandao3",
        ]));
        set("area", "tangmen");
        set("objects", ([__DIR__"npc/qingshe" : 1,__DIR__"npc/jinshe" : 1,]));
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}