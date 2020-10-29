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
                "east"  : __DIR__"maze37",
                "south" : __DIR__"maze29",
                "west"  : __DIR__"maze57",
                "north" : __DIR__"maze40",
        ]));

        set("item_desc", ([
                "shibei" : "
　　涣：亨。 王假有庙，利涉大川，利贞。
　　初六：用拯马壮，吉。
　　九二：涣奔其机，悔亡。
　　六三：涣其躬，无悔。
　　六四：涣其群，元吉。 涣有丘，匪夷所思。
　　九五：涣汗其大号，涣王居，无咎。
　　上九：涣其血，去逖出，无咎。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 59, me);
        check_count(me, 59);
        return;
}