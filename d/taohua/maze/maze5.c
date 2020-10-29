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
                "east"  : __DIR__"maze8",
                "south" : __DIR__"maze26",
                "north" : __DIR__"maze9",
        ]));

        set("item_desc", ([
                "shibei" : "
　　需：有孚，光亨，贞吉。 利涉大川。
　　初九：需于郊。 利用恒，无咎。
　　九二：需于沙。 小有言，终吉。
　　九三：需于泥，致寇至。
　　六四：需于血，出自穴。
　　九五：需于酒食，贞吉。
　　上六：入于穴，有不速之客三人来，敬之终吉。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 5, me);
        check_count(me, 5);
        return;
}