// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

#include "maze.h"

void create()
{
        set("short", "石阵");
        set("long", @LONG
这是一座由约莫两人多高的大石块构成的乱石阵，规模似乎不大，但
抬眼望去，四周尽是重重叠叠的嶙峋怪石，完全看不出有路通向石阵之外，
加之阵中常年雾气弥漫，更让人摸不清头绪。石块下有一块斜倒的石碑(s
hibei)，半埋在浮土中。
LONG );

        set("exits", ([
                "east"  : __DIR__"maze13",
                "south" : __DIR__"maze47",
                "west"  : __DIR__"maze44",
        ]));

        set("item_desc", ([
                "shibei" : "
　　讼：有孚，窒。 惕中吉。 终凶。 利见大人，不利涉大川。
　　初六：不永所事，小有言，终吉。
　　九二：不克讼，归而逋，其邑人三百户，无眚。
　　六三：食旧德，贞厉，终吉，或从王事，无成。
　　九四：不克讼，复自命，渝安贞，吉。
　　九五：讼元吉。
　　上九：或锡之□带，终朝三褫之。

□  ＝ 上般 下革
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 6, me);
        check_count(me, 6);
        return;
}