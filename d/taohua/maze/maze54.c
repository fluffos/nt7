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
                "east"  : __DIR__"maze51",
                "south" : __DIR__"maze61",
                "west"  : __DIR__"maze62",
                "north" : __DIR__"maze38",
        ]));

        set("item_desc", ([
                "shibei" : "
　　归妹：征凶，无攸利。
　　初九：归妹以娣，跛能履，征吉。
　　九二：眇能视，利幽人之贞。
　　六三：归妹以须，反归以娣。
　　九四：归妹愆期，迟归有时。
　　六五：帝乙归妹，其君之袂，不如其娣之袂良，月几望，吉。
　　上六：女承筐无实，士□羊无血，无攸利。
□  ＝ 圭 ＋ 刂
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 54, me);
        check_count(me, 54);
        return;
}