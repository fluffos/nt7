//wkantai2.c  by Lonely

#include <room.h>

inherit ROOM;

void create()
{        
        set("short", "西较武场看台");
        set("long",
"这是唐门的西较武场看台。看台上除了几排座位外，中间设了三张金\n"
"铸银雕的太师椅。观看比武大赛的最佳位置，就在这个看台上。当然，唐\n"
"门主持大赛的掌权者们的座位，也就设在这里。你站在看台上，斗志激昂。\n"
"这里的西面，是西较武场，南北各有一个看台。东面是东较武场的入口。\n"
);        
        set("no_steal", "1");
        set("no_fight", "1");
        set("exits", ([
                "east" : __DIR__"wrukou",
                "north" : __DIR__"wkantai1",
                "south" : __DIR__"wkantai3",
        ]));
        setup();
        replace_program(ROOM);
}