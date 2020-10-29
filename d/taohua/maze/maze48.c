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
                "east"  : __DIR__"maze29",
                "south" : __DIR__"maze18",
                "west"  : __DIR__"maze3",
                "north" : __DIR__"maze57",
        ]));

        set("item_desc", ([
                "shibei" : "
　　井：改邑不改井，无丧无得，往来井井。汔至，亦未□①井，羸其瓶，
        凶。
　　初六：井泥不食，旧井无禽。
　　九二：井谷射鲋，瓮敝漏。
　　九三：井渫不食，为我民恻，可用汲，王明，并受其福。
　　六四：井□②，无咎。
　　九五：井冽，寒泉食。
　　上六：井收勿幕，有孚无吉。
□②  ＝ 上 秋 下 瓦
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 48, me);
        check_count(me, 48);
        return;
}