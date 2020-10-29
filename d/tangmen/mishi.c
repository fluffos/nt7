//mishi.c  by Lonely

#include <room.h>

inherit ROOM;

void create()
{        
        set("short", "秘室");
        set("long",
"这是一间秘室。据说唐门的暗器制法以及毒药的炼法就收藏在这里。\n"
"但是屋里什么都没有，不知传闻是否属实。这时，一阵异味擦肩而过，不\n"
"是香，不是臭，更不是酸甜苦辣，只是一种感觉。难道，唐七味以嗅觉发\n"
"暗器的绝技，就是来自这里。南面是唐门的后院。\n"
);        
        set("exits", ([
                "south" : __DIR__"houyuan",
        ]));
        setup();
        replace_program(ROOM);
}