// Code of ShenZhou
// Room: didao_w_1.c 地道西
// Zhangchi 7/00

inherit ROOM;
#include "didao.h"

void create()
{
        set("short", "地道");
        set("long", @LONG
这是一条刚刚挖成的地道，看样子是往西延伸。
LONG );
        set("exits", ([
                "east": "/d/mingjiao/didao/didao_w",
]));
        
        set("cost", 1);
        set("valid_dig","west");

        setup();
//        replace_program(ROOM);
}

void init()
{
        int num=get_room("west");
        if (num >= 2)
                set("exits/west","/d/mingjiao/didao/didao_w_2");
        else
                delete("exits/west");

        add_action("do_dig","wa");
        add_action("do_dig","dig");
}
