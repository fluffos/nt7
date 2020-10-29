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
                "east"  : __DIR__"maze54",
                "south" : __DIR__"maze53",
                "west"  : __DIR__"maze16",
                "north" : __DIR__"maze56",
        ]));

        set("item_desc", ([
                "shibei" : "
　　小过：亨，利贞，可小事，不可大事。飞鸟遗之音，不宜上宜下，大
          吉。
　　初六：飞鸟以凶。
　　六二：过其祖，遇其妣；不及其君，遇其臣；无咎。
　　九三：弗过防之，从或戕之，凶。
　　九四：无咎，弗过遇之。 往厉必戒，勿用永贞。
　　六五：密云不雨，自我西郊，公弋取彼在穴。
　　上六：弗遇过之，飞鸟离之，凶，是谓灾眚。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 62, me);
        check_count(me, 62);
        return;
}