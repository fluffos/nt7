//ejiaowu.c  by Lonely

#include <room.h>

inherit ROOM;

void create()
{        
        set("short", "东较武场");
        set("long",
"这是唐门的东较武场。一片开阔平坦的空地，最适合比试武功。不要\n"
"看平日冷冷清清，唐门定期举行的比武大会，有一半的赛事在这里进行。\n"
"较场东侧，排放了几个兵器架。较场的西面，并排着三个看台，比赛时候\n"
"那惊天动地的喝彩声，全都来自这里。\n"
);        
        set("no_steal", "1");
        set("no_fight", "1");
        set("exits", ([
                "west" : __DIR__"ekantai2",
        ]));
        set("outdoors", "tangmen");
        setup();
        replace_program(ROOM);
}