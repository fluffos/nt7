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
                "east"  : __DIR__"maze57",
                "south" : __DIR__"maze3",
                "west"  : __DIR__"maze61",
                "north" : __DIR__"maze51",
        ]));

        set("item_desc", ([
                "shibei" : "
　　益：利有攸往，利涉大川。
　　初九：利用为大作，元吉，无咎。
　　六二：或益之，十朋之龟弗克违，永贞吉。 王用享于帝，吉。
　　六三：益之用凶事，无咎。 有孚中行，告公用圭。
　　六四：中行，告公从。 利用为依迁国。
　　九五：有孚惠心，勿问元吉。 有孚惠我德。
　　上九：莫益之，或击之，立心勿恒，凶。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 42, me);
        check_count(me, 42);
        return;
}