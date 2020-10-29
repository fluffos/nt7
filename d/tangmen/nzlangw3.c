//nzlangw3.c                四川唐门—青石小路

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
                        "east" : __DIR__"nzlangw2",
                        "west" : __DIR__"shufang",
                        "north" : __DIR__"brestroom",
                        "south" : __DIR__"grestroom",
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen");
        setup();
//        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if( (dir == "north") && (query("gender", me) != "男性") )
                return notify_fail("喂！那里都是男人呀！\n");

        if( (dir == "south") && (query("gender", me) != "女性") )
                return notify_fail("喂！擅闯女弟子休息室，犯门规的！\n");

        return ::valid_leave(me, dir);
}