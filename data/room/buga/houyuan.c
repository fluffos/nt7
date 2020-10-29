// File(/data/room/buga/houyuan.c) of buga's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "虫洞后院");
	set ("long", @LONG
这是虫洞的后院，种着一些花草，大部分是都不知名的野生花草。
不过花儿开起来也看上去也非常漂亮。有时红臭虫读书练武疲倦了，
就到这里稍作片刻以休息，也有时友人来到这里，大家在这里切磋一
下武艺。 
LONG );

        setup();

        set("exits", ([
                "south"  : __DIR__"dating",
        ]));

        set("outdoors", "playertown");
        set("sleep_room", 1);

        set("room_owner", "红臭虫");
        set("room_name", "虫洞");
        set("room_id", "bugaa");
        set("room_owner_id", "buga");
        set("room_position", "碎石小道");
}

void init()
{
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
