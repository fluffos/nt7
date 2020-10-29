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
                "east"  : __DIR__"maze40",
                "south" : __DIR__"maze57",
                "west"  : __DIR__"maze51",
                "north" : __DIR__"maze50",
        ]));

        set("item_desc", ([
                "shibei" : "
　　恒：亨，无咎，利贞，利有攸往。
　　初六：浚恒，贞凶，无攸利。
　　九二：悔亡。
　　九三：不恒其德，或承之羞，贞吝。
　　九四：田无禽。
　　六五：恒其德，贞，妇人吉，夫子凶。
　　上六：振恒，凶。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 32, me);
        check_count(me, 32);
        return;
}