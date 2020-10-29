// File(/data/room/ovo/yanwu2.c) of ovo's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "东北偏北演武厅");
	set ("long", @LONG
这是东北偏北的演武厅，有时有些江湖朋友来会，想一试身手，
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

        set("room_owner", "小球球");
        set("room_name", "东北偏北");
        set("room_id", "dan");
        set("room_owner_id", "ovo");
        set("room_position", "碎石小道");
}
