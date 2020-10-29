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
                "east"  : __DIR__"maze6",
                "south" : __DIR__"maze28",
                "west"  : __DIR__"maze25",
        ]));

        set("item_desc", ([
                "shibei" : "
　　□①：女壮，勿用取女。
　　初六：系于金□②，贞吉，有攸往，见凶，羸豕踟躅。
　　九二：包有鱼，无咎，不利宾。
　　九三：臀无肤，其行次且，厉，无大咎。
　　九四：包无鱼，起凶。
　　九五：以杞包瓜，含章，有陨自天。
　　上九：□①其角，吝，无咎。
□① ＝ 女 ＋ 后
□② ＝ 木 ＋ 尼
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 44, me);
        check_count(me, 44);
        return;
}