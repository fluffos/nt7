//houzhai.c                唐门世家—走廊

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "后宅");
        set("long",
"这里是莲云阁后宅。从这里向北就是唐门的代表唐老太太的寝室据闻\n"
"外人要见到唐老太太势比登天还难，从这里向东是一间柴房，向西是通向\n"
"后院的小路。\n"
);
        set("exits", ([
                        "north" : __DIR__"nzlang2",
                        "south" : __DIR__"dating",
                        "southwest" : __DIR__"chaifang",
        ]));
        create_door("southwest","木门","northeast",DOOR_CLOSED);
        set("objects", ([
                __DIR__"npc/tangkan" : 1,
        ]));
        set("area", "tangmen");
        setup();
//        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if( (dir == "north") && (query("family/family_name", me) != "唐门世家") )
                return notify_fail("你不是唐门中人，不能再向前走了！\n");

        return ::valid_leave(me, dir);
}