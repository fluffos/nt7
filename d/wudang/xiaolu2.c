#include <room.h>
inherit ROOM;

void create()
{
        set("short", "林间小径");
        set("long", @LONG
你走在一条小径上，两旁种满了竹子，修篁森森，绿荫满地，除
了竹叶声和鸟鸣声，听不到别的动静。南面似乎有一座简陋的小院。
LONG );
        set("exits", ([
                "south" : __DIR__"xiaoyuan.c",
                "north" : __DIR__"xiaolu1",
        ]));
        set("objects", ([
                CLASS_D("wudang") + "/qingfeng": 1,
                CLASS_D("wudang") + "/mingyue": 1,
        ]));
        create_door("south", "竹门", "north", DOOR_CLOSED);
        set("outdoors", "wudang");
        set("coor/x", -370);
        set("coor/y", -330);
        set("coor/z", 90);
        setup();
}
