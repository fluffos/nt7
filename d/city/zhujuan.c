// Room: /city/zhujuan.c
// YZC 1995/12/04 

#include <room.h>

inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", "猪圈");
        set("long", @LONG
这里是一个臭烘烘的猪圈，栏上挂着一个牌子(paizi)。
LONG );
        set("no_fight", 1);
        set("no_sleep_room",1);
        set("item_desc", ([
                "paizi" : "大家一起发呆，把泥潭变成猪的世界。\n",
        ]));
        set("exits", ([
                "up"   : "/d/city/kedian",
        ]));

        setup();
}
