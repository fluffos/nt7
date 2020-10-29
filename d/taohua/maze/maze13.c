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
                "south" : __DIR__"maze49",
                "west"  : __DIR__"maze6",
        ]));

        set("item_desc", ([
                "shibei" : "
　　同人：同人于野，亨。 利涉大川，利君子贞。
　　初九：同人于门，无咎。
　　六二：同人于宗，吝。
　　九三：伏戎于莽，升其高陵，三岁不兴。
　　九四：乘其墉，弗克攻，吉。
　　九五：同人，先号啕而后笑。 大师克相遇。
　　上九：同人于郊，无悔。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 13, me);
        check_count(me, 13);
        return;
}