//tmbingqi.c

#include "/d/tangmen/npc/job1.h";

void create()
{
        set("short", "兵器铺");
        set("long",
"这是唐门开的兵器铺，中心摆着一个展览台，台上有许多暗器，不过\n"
"这些暗器有些古怪，不是一般武林人士会用的。它们是专门为唐门弟子提\n"
"供的，但都是个普通的暗器，对于唐门弟子来说。一位唐门弟子正满头大\n"
"汗接待着往来的客人。\n"
);
        set("exits", ([
                "west" : __DIR__"ndajie",
        ]));
        set("objects", ([
                __DIR__"npc/dizi2": 1,
        ]));
        set("no_clean_up", 1);
        set("no_fight", 1);
        setup();
        
}
