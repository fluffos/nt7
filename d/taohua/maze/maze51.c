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
                "east"  : __DIR__"maze32",
                "south" : __DIR__"maze42",
                "west"  : __DIR__"maze54",
                "north" : __DIR__"maze21",
        ]));

        set("item_desc", ([
                "shibei" : "
　　震：亨。 震来□①□①，笑言哑哑。 震惊百里，不丧匕鬯。
　　初九：震来□①□①，后笑言哑哑，吉。
　　六二：震来厉，亿丧贝，跻于九陵，勿逐，七日得。
　　六三：震苏苏，震行无眚。
　　九四：震遂泥。
　　六五：震往来厉，亿无丧，有事。
　　上六：震索索，视矍矍，征凶。 震不于其躬，于其邻，无咎。 婚媾
          有言。
□① ＝ 左上小 左中曰 左下小 右虎
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 51, me);
        check_count(me, 51);
        return;
}