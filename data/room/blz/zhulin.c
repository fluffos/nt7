// File(/data/room/blz/zhulin.c) of blz's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "竹林");
	set ("long", @LONG
这里种着好大一片竹林，非常幽静。风一起就听竹叶沙沙的响，
有时暴雪就去听涛阁默听竹浪涛声，参悟武功。 
LONG );

        set("exits", ([
                "west" : __DIR__"huayuan",
                "east" : __DIR__"tingtao",
        ]));

        set("outdoors", "playertown");
        set("sleep_room", 1);
        setup();

        set("room_owner", "暴雪");
        set("room_name", "逍遥洞");
        set("room_id", "blz");
        set("room_owner_id", "blz");
        set("room_position", "青砖路");
}
