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
                "east"  : __DIR__"maze35",
                "south" : __DIR__"maze34",
                "north" : __DIR__"maze43",
        ]));

        set("item_desc", ([
                "shibei" : "
　　大有：元亨。 
　　初九：无交害，匪咎，艰则无咎。
　　九二：大车以载，有攸往，无咎。
　　九三：公用亨于天子，小人弗克。
　　九四：匪其彭，无咎。
　　六五：厥孚交如，威如；吉。
　　上九：自天佑之，吉无不利。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 14, me);
        check_count(me, 14);
        return;
}