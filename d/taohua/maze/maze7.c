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
                "east"  : __DIR__"maze36",
                "west"  : __DIR__"maze46",
                "north" : __DIR__"maze4",
        ]));

        set("item_desc", ([
                "shibei" : "
　　师：贞，丈人，吉无咎。
　　初六：师出以律，否臧凶。
　　九二：在师中，吉无咎，王三锡命。
　　六三：师或舆尸，凶。
　　六四：师左次，无咎。
　　六五：田有禽，利执言，无咎。长子帅师，弟子舆尸，贞凶。
　　上六：大君有命，开国承家，小人勿用。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 7, me);
        check_count(me, 7);
        return;
}