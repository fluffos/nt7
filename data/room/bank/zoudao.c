// File(/data/room/bank/zoudao.c) of bank's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "走道");
	set ("long", @LONG
这是连接正厅和大门的一条走道，两旁都是木制墙板，前面就是
迎客厅。 
LONG );

        set("exits", ([
                "north"  : __DIR__"yingke",
                "south"  : __DIR__"qianting",
        ]));

        set("gate", "close");

        set("objects", ([
                "/d/room/roomnpc/yahuan" : 1,
        ]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "钱庄");
        set("room_name", "金风细雨楼");
        set("room_id", "gold");
        set("room_owner_id", "bank");
        set("room_position", "[1;33m名人堂[2;37;0m");
}

void init()
{
        add_action("do_push", "push");
        add_action("do_close", "close");
}

int do_push(string arg)
{
        object me;
        object room;

        if (query("gate") == "open")
                return notify_fail("大门开着呢，你还推什么？\n");

        me = this_player();
        message("vision",  "你用力推了推大门，就听大门“吱呀呀”的被人推开了。\n",
                           this_object());
    
        room = get_object(__DIR__"qianting");
        message("vision", "大门“吱呀呀”的被人推开了。\n", room);
        set("gate", "open");
        set("exits/south", __DIR__"qianting");
        set("exits/north", __FILE__, room);
        set("gate", "open", room);
        remove_call_out("do_close");
        call_out("do_close", 10, 0, 1);
        return 1;
}

int do_close(string arg, int n)
{
        object me;
        object room;

        if (query("gate") == "close")
                return notify_fail("大门关着呢，你还再关一遍？\n");

        if (! n)
        {
                me = this_player();
                message("vision", me->name() + "走上前去，用力合上大门。\n",
                        this_object());
        } else
        {
                message("vision", "大门“吱呀呀”的被人关上了。\n",
                        this_object());
        }

        room = get_object(__DIR__"qianting");
        message("vision", "大门“吱呀呀”的被人关上了。\n", room);
        set("gate", "close");
        delete("exits/south");
        set("gate", "close", room);
        delete("exits/north", room);
        return 1;
}
