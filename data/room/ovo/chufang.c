// File(/data/room/ovo/chufang.c) of ovo's room
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
此处便是东北偏北的厨房，只间几个仆人忙来忙去，不得歇息。
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

        set("room_owner", "小球球");
        set("room_name", "东北偏北");
        set("room_id", "dan");
        set("room_owner_id", "ovo");
        set("room_position", "碎石小道");
}
