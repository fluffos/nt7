//wting.c                四川唐门—西偏厅

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西偏厅");
        set("long",
"这里是莲云阁西侧的偏厅。一些唐门弟子喜欢到这里海阔天空，聚首\n"
"闲谈。厅内摆设了器具桌椅，厅外溪流潺潺，草木葱葱。听说，唐门最漂\n"
"亮的那位女弟子，常在这里徘徊，默默地思念他那远方的情郎。\n"
);
        set("exits", ([
                "east" : __DIR__"lianyunge",
        ]));
        set("objects", ([
                CLASS_D("tangmen") + "/tangfang" : 1,
        ]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}