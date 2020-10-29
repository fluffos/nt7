// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// 增加(discuss <对象> <次数> )功能 

inherit ROOM;

#include "discuss.h"
#include <ansi.h>

void create()
{
        set("short", "练功房");
        set("long", @LONG
这是桃花岛弟子的练功房。屋子东半部散放着几个蒲团，供诸弟子打
坐吐纳，调气养息，修练内功之用。西半部地上则绘着伏羲六十四卦的方
位卦象，大概是修习奇门遁甲所用。书架上有一些经书。
LONG );
         set("exits", ([
                "west" : __DIR__"changlang",
        ]));

         set("objects", ([
                __DIR__"obj/tiexiao" : 1,
                "/clone/weapon/zhuxiao" : 1,
                __DIR__"obj/yijing3" : 1,
                "/clone/misc/bagua"   : 1,
                "/clone/misc/xiang"   : 1,
                "/d/taohua/obj/zhuxiao" : 1,
        ]));

        set("no_fight", 1);
        set("coor/x", 9000);
        set("coor/y", -2940);
        set("coor/z", 0);
        setup();
//        replace_program(ROOM);
}

void init()
{
        add_action("do_discuss", "discuss");
        add_action("do_answer", "answer");
        add_action("do_answer", "da");
}