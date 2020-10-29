//neiyuan.c                四川唐门—内院

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "内院");
        set("long",
"这里是莲云阁内院。从这里向北就是唐门的核心唐老太太的寝室据闻\n"
"外人要见到唐老太太势比登天还难，从这里向东是一间柴房，向西是通向\n"
"后院的小路。\n"
);
        set("exits", ([
                        "south" : __DIR__"nzlang1",
                        "north" : __DIR__"nzlangn1",
        ]));
        set("objects", ([
                __DIR__"npc/tangsi" : 1,
        ]));
        set("area", "tangmen");
        setup();
}

int valid_leave(object me, string dir)
{
        if( (dir == "north") && (query("family/family_name", me) != "唐门世家") && 
                !wizardp(me) && (objectp( present("tang si", environment(me)) ) ))
                return notify_fail("唐思一伸手，说道：“你不是唐门中人，不能再向前走了！”\n");
        else
                return ::valid_leave(me, dir);
}