// File(/data/room/xigua/yanwu2.c) of xigua's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "水果摊演武厅");
	set ("long", @LONG
这是水果摊的演武厅，有时有些江湖朋友来会，想一试身手，就
在这里比武较量。 
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

        set("room_owner", "西瓜");
        set("room_name", "水果摊");
        set("room_id", "sgt");
        set("room_owner_id", "xigua");
        set("room_position", "碎石小道");
}
