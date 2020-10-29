// File(/data/room/bank/chufang.c) of bank's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

string *names = ({
        "/d/shaolin/obj/mala-doufu",
        "/d/shaolin/obj/bocai-fentiao",
        "/d/shaolin/obj/shanhu-baicai",
        "/d/shaolin/obj/liuli-qiezi",
        "/d/shaolin/obj/mizhi-tianou",
        "/d/shaolin/obj/jiaxin-biji",
        "/d/shaolin/obj/basi-shanyao",
        "/d/shaolin/obj/furong-huagu",
});

void create()
{
        set("short", "厨房");
	set ("long", @LONG
此处便是金风细雨楼的厨房，只间几个仆人忙来忙去，不得歇息。
LONG );

        set("exits", ([
                "east" : __DIR__"houyuan",
        ]));

        set("objects", ([
                names[random(sizeof(names))] : 1,
                names[random(sizeof(names))] : 1,
                names[random(sizeof(names))] : 1,
                "/d/room/roomobj/rice"  : 2,
                "/d/room/roomobj/soup"  : 2,
                "/d/room/roomobj/mantou": 3,
                "/d/room/roomnpc/puren" : 2 + random(3),
        ]));

        set("resource/water", 1);
        set("no_sleep_room", 1);
        setup();

        set("room_owner", "钱庄");
        set("room_name", "金风细雨楼");
        set("room_id", "gold");
        set("room_owner_id", "bank");
        set("room_position", "[1;33m名人堂[2;37;0m");
}
