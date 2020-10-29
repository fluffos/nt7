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
                "south" : __DIR__"maze37",
                "west"  : __DIR__"maze40",
                "north" : __DIR__"maze30",
        ]));

        set("item_desc", ([
                "shibei" : "
　　丰：亨，王假之，勿忧，宜日中。
　　初九：遇其配主，虽旬无咎，往有尚。
　　六二：丰其□①，日中见斗，往得疑疾，有孚发若，吉。
　　九三：丰其沛，日中见昧，折其右肱，无咎。
　　九四：丰其□①，日中见斗，遇其夷主，吉。
　　六五：来章，有庆誉，吉。
　　上六：丰其屋，□①其家，窥其户，□②其无人，三岁不见，凶。
□① ＝ 上艹 下部
□② ＝ 外门 内臭  阒的误笔?
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 55, me);
        check_count(me, 55);
        return;
}