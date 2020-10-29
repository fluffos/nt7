// File(/data/room/bank/zhulin.c) of bank's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "竹林");
	set ("long", @LONG
这里种着好大一片竹林，非常幽静。风一起就听竹叶沙沙的响，
有时钱庄就去听涛阁默听竹浪涛声，参悟武功。 
LONG );

        set("exits", ([
                "west" : __DIR__"huayuan",
                "east" : __DIR__"tingtao",
        ]));

        set("outdoors", "unknow");
        set("sleep_room", 1);
        setup();

        set("room_owner", "钱庄");
        set("room_name", "金风细雨楼");
        set("room_id", "gold");
        set("room_owner_id", "bank");
        set("room_position", "[1;33m名人堂[2;37;0m");
}
