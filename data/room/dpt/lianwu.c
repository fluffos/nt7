// File(/data/room/dpt/lianwu.c) of dpt's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "练武场");
	set ("long", @LONG
此处便是游戏基地的练武场，人在江湖，武功万万不可荒废。 
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
    
        set("room_owner", "多炮塔");
        set("room_name", "游戏基地");
        set("room_id", "gamebase");
        set("room_owner_id", "dpt");
        set("room_position", "南海之滨");
}
