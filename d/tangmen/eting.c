//eting.c                四川唐门—东偏厅

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "东偏厅");
        set("long",
"这里是莲云阁东侧的偏厅。一些唐门弟子喜欢到这里海阔天空，聚首\n"
"闲谈。厅内摆设了器具桌椅，厅外溪流潺潺，草木葱葱。一阵夹带着泥土\n"
"气息的凉风飘进来，你感到精神为之一爽。\n"
);
        set("exits", ([
             "west" : __DIR__"lianyunge",
        ]));
        set("objects", ([
                CLASS_D("tangmen") + "/tangque" : 1,
        ]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}