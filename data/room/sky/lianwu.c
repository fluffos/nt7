// File(/data/room/sky/lianwu.c) of sky's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "练武场");
	set ("long", @LONG
此处便是海南岛的练武场，人在江湖，武功万万不可荒废。 
LONG );

        set("exits", ([
                "west" : __DIR__"houyuan",
        ]));

        set("objects", ([
                "/clone/npc/mu-ren" : 4,
        ]));

        set("outdoors", "nanhai");
        set("no_sleep_room", 1);

        setup();
    
        set("room_owner", "灭下");
        set("room_name", "海南岛");
        set("room_id", "sky");
        set("room_owner_id", "sky");
        set("room_position", "南海之滨");
}
