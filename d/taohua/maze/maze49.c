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
                "south" : __DIR__"maze30",
                "west"  : __DIR__"maze47",
                "north" : __DIR__"maze13",
        ]));

        set("item_desc", ([
                "shibei" : "
　　革：己日乃孚，元亨利贞，悔亡。
　　初九：巩用黄牛之革。
　　六二：己日乃革之，征吉，无咎。
　　九三：征凶，贞厉，革言三就，有孚。
　　九四：悔亡，有孚改命，吉。
　　九五：大人虎变，未占有孚。
　　上六：君子豹变，小人革面，征凶，居贞吉。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 49, me);
        check_count(me, 49);
        return;
}