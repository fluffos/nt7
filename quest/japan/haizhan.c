// /job/japan/haizhan.c
// by akuma 10:52 AM 11/30/2003
// source from hanghai_room.c

#include <ansi.h>
inherit ROOM;
#define MST        __DIR__"haizhan_master"                // 经纬仪，游戏指令主支持

void create()
{
        set("short", "大海中");
        set("long", @LONG
茫茫大海之中，左右舰队跟随浩浩荡荡冲向日本舰队。
LONG);
        set("no_steal", "1");
        set("no_sleep_room", "1");
        set("cost", 0);
        setup();
}

void init()
{
        add_action("do_game", "haizhan");
        add_action("do_quit", "quit");
}

int do_game(string arg)
{
        object me = this_player(), mst_obj;

        if ( !arg || arg != "开始" ) return 0;        // "game over" 等操作，由 MST 物件进行。

        if( !query_temp("job/fleet", me))return notify_fail("你正在使入黄海海战区。\n");

        if ( file_size( MST + ".c" ) < 1 ) return notify_fail("海战暂停，老佛爷叫歇了。\n");

        write("\n你带这舰队慢慢地驶入黄海战区……\n\n");
        mst_obj = new( MST );
        mst_obj->new_game(me);
        mst_obj->move(me);
        return 1;
}

int valid_leave(object me, string dir)
{
        if( query_temp("job/haizhan", me))return notify_fail("战事已经开始，不能临阵脱逃。\n");

        return ::valid_leave(me, dir);
}

int do_quit()
{
        write("这里不能退出游戏。\n");
        return 1;
}