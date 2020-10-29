// File(/data/room/buga/xiaoyuan.c) of buga's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "虫洞小院");
	set ("long", @LONG
这里是一个四四方方的院子，院墙都是用红砖砌成，不算高，但
是非常清爽利落。院中几棵古木成荫，隐然有一种世外桃源的感觉。
院子外面隐约是碎石小道，院子的北面有一扇木门。 
LONG );

        set("room_key", "1 of buga");
        setup();

        set("exits", ([
                "out"    : "/d/room/playtown/road16",
        ]));

        set("outdoors", "playertown");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dating",
        ]));
    
        set("room_owner", "红臭虫");
        set("room_name", "虫洞");
        set("room_id", "bugaa");
        set("room_owner_id", "buga");
        set("room_position", "碎石小道");
}
