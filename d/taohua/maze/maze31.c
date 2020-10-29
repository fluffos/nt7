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
                "east"  : __DIR__"maze58",
                "south" : __DIR__"maze56",
                "west"  : __DIR__"maze45",
                "north" : __DIR__"maze33",
        ]));

        set("item_desc", ([
                "shibei" : "
　　咸：亨，利贞，取女吉。
　　初六：咸其拇。
　　六二：咸其腓，凶，居吉。
　　九三：咸其股，执其随，往吝。
　　九四：贞吉悔亡，憧憧往来，朋从尔思。
　　九五：咸其□，无悔。
　　上六：咸其辅，颊，舌。
□  ＝ 月 ＋ 每
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 31, me);
        check_count(me, 31);
        return;
}