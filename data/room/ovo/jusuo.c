// File(/data/room/ovo/jusuo.c) of ovo's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "居所");
	set ("long", @LONG
这就是东北偏北主人小球球休息、读书的地方。楼上就是主人的
卧室，西面则是书房。 
LONG );

        set("exits", ([
                "up"   : __DIR__"woshi",
                "west" : __DIR__"shufang",
        ]));

        set("no_sleep_room", 1);
        setup();

        set("KEY_DOOR", ([
                "exit" : "east",
                "room" : __DIR__"huayuan",
        ]));
    
        set("room_owner", "小球球");
        set("room_name", "东北偏北");
        set("room_id", "dan");
        set("room_owner_id", "ovo");
        set("room_position", "碎石小道");
}
