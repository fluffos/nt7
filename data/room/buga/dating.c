// File(/data/room/buga/dating.c) of buga's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "虫洞大厅");
	set ("long", @LONG
这就是虫洞主人红臭虫迎送客人的地方。正中有些桌椅，侧面是
两扇屏风。东首是主人红臭虫的房间，有一扇木门虚掩着。南边是大
门，出去就是院子。 
LONG );

        setup();

        set("exits", ([
                "east"   : __DIR__"woshi",
                "north"  : __DIR__"houyuan",
        ]));

        create_door("east", "木门", "west", DOOR_CLOSED);

        set("no_sleep_room", 1);

        set("KEY_DOOR", ([
                "exit" : "south",
                "room" : __DIR__"xiaoyuan",
        ]));
    
        set("room_owner", "红臭虫");
        set("room_name", "虫洞");
        set("room_id", "bugaa");
        set("room_owner_id", "buga");
        set("room_position", "碎石小道");
}
