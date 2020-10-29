// File(/data/room/bank/huayuan.c) of bank's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "后花园");
	set ("long", @LONG
这是金风细雨楼的后花园，种着一些钱庄采自五湖四海、名山大
川的奇花异草，美丽非常。钱庄有时读书练武疲倦了，就到这里稍作
休息，观赏花草以怡情自乐，或许能突发灵感，有所领悟。西面就是
通往主人居所的铁门，东面则是一片竹林。 
LONG );

        set("exits", ([
                "north"  : __DIR__"caidi",
                "south"  : __DIR__"houyuan",
                "east"   : __DIR__"zhulin",
        ]));

        set("outdoors", "unknow");
        set("sleep_room", 1);
        set("room_key", "1 of bank");
        setup();

        set("KEY_DOOR", ([
                "exit" : "west",
                "room" : __DIR__"jusuo",
        ]));
    
        set("room_owner", "钱庄");
        set("room_owner_id", "bank");
        set("room_name", "金风细雨楼");
        set("room_id", "gold");
        set("room_position", "[1;33m名人堂[2;37;0m");
}

void init()
{
        ::init();
        add_action("do_sit", "sit");
        delete_temp("has_sit", this_player());
}

int do_sit(string arg)
{
        object me;

        me = this_player();
        if( query_temp("has_sit", me) )
        {
                message_vision("$N坐在那里摇啊摇，好不惬意。\n", me);
                return 1;
        }

        message_vision("$N找了的地方作了下来，看上去轻松多了。\n", me);
        set_temp("has_sit", 1, me);
        return 1;
}

int valid_leave(object me, string dir)
{
        if( query_temp("has_sit", me) )
        {
                message_vision("$N掸掸尘土，站了起来。\n", me);
                delete_temp("has_sit", me);
        }

        return ::valid_leave(me, dir);
}
