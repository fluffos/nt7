//nzlange1.c                四川唐门—青石小路

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青石小路");
        set("long",
"这是一条青石铺就的小路。由于来来往往的人数太多，粗糙的青石已\n"
"经被磨的光滑如镜。一些唐门的弟子往来穿梭，这里还真是很热闹。这里向\n"
);
        set("exits", ([
                "north" : __DIR__"chaifang",
                "west"  : __DIR__"nzlangn3",
                "east"  : __DIR__"nzlange2",
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}