// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "药房");
        set("long", @LONG
这里是黄药师储藏平日炼制药材的地方，桃花岛弟子也经常到这里来
取用一些自己合用的药物。散发出阵阵沁人心肺花香的就是桃花岛名闻天
下的九花玉露丸，气味刺鼻的则是解毒灵药田七鲨胆散，颜色猩红如血的
是疗伤圣药无常丹。北面是一道长廊。
LONG );
        set("exits", ([
                "north" : __DIR__"changlang2",
        ]));
        
        set("objects", ([
                __DIR__"npc/mianfeng" : 1,
        ]));
        
        set("coor/x", 8980);
        set("coor/y", -2960);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

/*
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
*/