// File(/data/room/sky/zhulin.c) of sky's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "竹林");
	set ("long", @LONG
这里种着好大一片竹林，非常幽静。风一起就听竹叶沙沙的响，
有时灭下就去听涛阁默听竹浪涛声，参悟武功。 
LONG );

        set("exits", ([
                "west" : __DIR__"huayuan",
                "east" : __DIR__"tingtao",
        ]));

        set("outdoors", "nanhai");
        set("sleep_room", 1);
        setup();

        set("room_owner", "灭下");
        set("room_name", "海南岛");
        set("room_id", "sky");
        set("room_owner_id", "sky");
        set("room_position", "南海之滨");
}
