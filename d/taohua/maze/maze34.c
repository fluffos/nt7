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
                "east"  : __DIR__"maze16",
                "south" : __DIR__"maze9",
                "north" : __DIR__"maze14",
        ]));

        set("item_desc", ([
                "shibei" : "
　　大壮：利贞。
　　初九：壮于趾，征凶，有孚。
　　九二：贞吉。
　　九三：小人用壮，君子用罔，贞厉。 羝羊触藩，羸其角。
　　九四：贞吉悔亡，藩决不羸，壮于大舆之□。
　　六五：丧羊于易，无悔。
　　上六：羝羊触藩，不能退，不能遂，无攸利，艰则吉。
□  ＝ 车 ＋ 复
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 34, me);
        check_count(me, 34);
        return;
}