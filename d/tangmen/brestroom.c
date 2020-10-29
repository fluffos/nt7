//brestroom.c  by Lonely

#include <room.h>

inherit ROOM;

void create()
{        
        set("short", "男弟子休息室");
        set("long",
"这是一个昏暗的房间，窗口被厚厚的黑布遮住，只有一丝光线从门缝\n"
"中透过，隐约的看到几个人躺在靠墙的大床上休息。\n"
);        
        set("valid_startroom",1);
        set("no_steal", "1");
        set("no_fight", "1");
        set("sleep_room",1);
        set("exits", ([
                "south" : __DIR__"nzlangw3",
        ]));
        setup();
        replace_program(ROOM);
}