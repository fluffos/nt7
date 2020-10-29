//                标准描述长度示例                                   |
// 仿某游戏而写成，名字似乎应该照原作，定为“小航海时代” ：）
// 原作很精简，确为休闲游戏之典范！是一款需要安装的，有简易图样的游戏。


// 本游戏由 hanghai_master.c (经纬仪) 支持主要指令。
// by naihe  2003-06-19  于茂名

#include <ansi.h>

inherit ROOM;

#define MST                __DIR__"hanghai_master"                // 经纬仪，游戏指令主支持


void create()
{
        set("short", HIC"〖小航海时代〗 游戏室"NOR);
        set("long", "
***********************************************
              〖小航海时代〗

    欢迎来到 小航海时代 游戏。这里是一个休闲
小游戏，您在游戏获得乐趣的同时，亦将能够得到
一定数量的MUD奖励，以资鼓励。

    进入游戏：         game start
    任何时候退出游戏： game over

    BY 奈何(naihe)    --2003.06.19
***********************************************
\n");
        set("no_fight", "1");
        set("no_steal", "1");
        set("no_sleep_room", "1");
        set("valid_startroom", 1); // 此两条分别为：非连线房间 及 起始房间
        set( "cost", 0 );

        set("exits", ([
            "out":  "/d/city/advice/advice",
        ]));

        setup();
}

void init()
{
        add_action("do_game", "game");
}

int do_game(string arg)
{
        object me = this_player(), mst_obj;

        if( !arg || arg != "start" )
                return 0;

// "game over" 等操作，由 MST 物件进行。


        if( query_temp("hanghai_gameing", me) )
                return notify_fail("你已身在游戏中！\n");

        if( file_size( MST + ".c" ) < 1 )
                return notify_fail("本游戏暂停开放！\n");

        write("\n========= 请稍候，正在执行操作…… ==========\n\n");

        mst_obj = new( MST );

        mst_obj->new_game(me);
        mst_obj->move(me);

        return 1;
}



int valid_leave(object me, string dir)
{
        if( query_temp("hanghai_gameing", me) )
                return notify_fail("你正在游戏中，不得离开！\n");

        return ::valid_leave(me, dir);
}