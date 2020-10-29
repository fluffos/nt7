// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from the
// Slough develop group

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
                "south" : __DIR__"maze63",
                "west"  : __DIR__"maze59",
                "north" : __DIR__"maze55",
        ]));

        set("item_desc", ([
                "shibei" : "
　　家人：利女贞。
　　初九：闲有家，悔亡。
　　六二：无攸遂，在中馈，贞吉。
　　九三：家人□□，悔厉吉；妇子嘻嘻，终吝。
　　六四：富家，大吉。
　　九五：王假有家，勿恤吉。
　　上九：有孚威如，终吉。
□  ＝ 口 ＋ 高
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 37, me);
        check_count(me, 37);
        return;
}