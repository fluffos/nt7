//shandao3.c                四川唐门—后山山道

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
                "northeast" : __DIR__"shandao4",
                "westdown" : __DIR__"shandao2",
                "southdown" : __DIR__"shanshi5",
        ]));
        set("area", "tangmen");
        set("objects", ([
                __DIR__"npc/wugong" : 1,
                __DIR__"npc/fushe" : 1,
        ]));
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}