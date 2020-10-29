#include <room.h>

inherit ROOM;

void create()
{
        set("short", "丛林小道");
        set("long", @LONG
这是一条僻静的丛林小道，小道上满是枯枝败叶，踩上去非
常松软，四周静悄悄的，偶尔传来几声鸟鸣。
LONG
        );
/*
        set("exits", ([
  "north" : __DIR__"yz_door",
        "southwest" : __DIR__"yaopu1",
]));
*/
        set("exits", ([
        "southeast" : __DIR__"gd3",
        "northwest" : __DIR__"xiaodao2",
]));

        set("outdoors", "yaowang");
        setup();
        create_door("southeast", "木门", "northwest", DOOR_CLOSED);
}
