// File(/data/room/dpt/yanwu2.c) of dpt's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "游戏基地演武厅");
	set ("long", @LONG
这是游戏基地的演武厅，有时有些江湖朋友来会，想一试身手，
就在这里比武较量。 
LONG );

        set("exits", ([
                "east" : __DIR__"yishiting",
        ]));

        set("objects", ([
                "/clone/weapon/zhubang" : 1,
                "/clone/weapon/zhujian" : 1,
                "/clone/weapon/mudao"   : 1,
        ]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "多炮塔");
        set("room_name", "游戏基地");
        set("room_id", "gamebase");
        set("room_owner_id", "dpt");
        set("room_position", "南海之滨");
}
