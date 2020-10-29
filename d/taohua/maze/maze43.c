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
                "east"  : __DIR__"maze45",
                "south" : __DIR__"maze14",
                "north" : __DIR__"maze1",
        ]));

        set("item_desc", ([
                "shibei" : "
　　□①：扬于王庭，孚号，有厉，告自邑，不利即戎，利有攸往。
　　初九：壮于前趾，往不胜为吝。
　　九二：惕号，莫夜有戎，勿恤。
　　九三：壮于□②，有凶。 君子□①□①，独行遇雨，若濡有愠，无咎。
　　九四：臀无肤，其行次且。 牵羊悔亡，闻言不信。
　　九五：苋陆□①□①，中行无咎。
　　上六：无号，终有凶。
□① ＝ 炔 － 火
□② ＝ 九 ＋ 页
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 43, me);
        check_count(me, 43);
        return;
}