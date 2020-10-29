// Create by BUNCH_D written by Lonely

#include <ansi.h>
inherit ROOM;

int is_bunch_room() { return 1; } 

void create()
{
        set("short", "空房间 - 请使用 cshort 来编辑标题");
        set("long", "这是一间什么也没有的空房间，请利用 clong 来编辑房间叙述。\n");
        
        set("exits", ([
                "north" : __DIR__"room9",
                "south" : __DIR__"room7",
        ]));

        setup();
}