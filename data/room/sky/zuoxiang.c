// File(/data/room/sky/zuoxiang.c) of sky's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "左厢房");
	set ("long", @LONG
这是海南岛的左厢房，是客人居住的地方。虽然不算奢华，却也
布置得非常舒适。一张床整齐干净，没有多少折纹，而窗帘厚大结实，
使屋内光线恰到好处。 
LONG );

        set("exits", ([
                "west" : __DIR__"zhongting",
        ]));

        set("sleep_room", 1);
        set("no_fight", 1);

        create_door("west", "木门", "east", DOOR_CLOSED);

        set("room_owner", "灭下");
        set("room_name", "海南岛");
        set("room_id", "sky");
        set("room_owner_id", "sky");
        set("room_position", "南海之滨");
}
