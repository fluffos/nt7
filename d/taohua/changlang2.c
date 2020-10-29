// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "长廊");
        set("long", @LONG
这是一道长长的由翠绿青竹搭成的走廊，周围种满翠竹，凤尾森森，
龙吟细细，令人精神为之一振。不知什麽地方飘来阵阵药香，似乎有一个
药房，左面有一间厢房，右面是水龙轩，北面是桃花弟子休息室。
LONG );
         set("exits", ([
                "north" : __DIR__"xiuxishi",
                "west"  : __DIR__"hyjuchu",
                "east"  : __DIR__"shuilong",
                "south" : __DIR__"yaofang",
        ]));
        /*
         set("objects", ([
                __DIR__"obj/tiexiao" : 1,
                __DIR__"obj/zhuxiao" : 2,
                __DIR__"obj/yijing3" : 1,
                __DIR__"obj/yijing4" : 1,
        ]));

        set("no_fight", 1);
        */
        set("coor/x", 8980);
        set("coor/y", -2950);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ( (!myfam || myfam["family_name"] != "桃花岛") && dir == "north" )
                return notify_fail("桃花岛不留外客，你不能住在这里！\n");

        if( query("gender", me) == "无性" && dir == "north" )
                return notify_fail("你不能住在这里！\n");

        return ::valid_leave(me, dir);
}