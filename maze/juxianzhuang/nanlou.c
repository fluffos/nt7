// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "南楼");
        set("long",  @LONG
这里是游府的南楼，游氏双雄的知交好友来府上做客大多居于此处。
此次英雄宴邀请的宾客之中，“铁面判官”单正声望既高，又与游氏双
雄交情匪浅，便将他安顿在这间厢房内暂住。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"  :  __DIR__"changlang4",
                "east"  :  __DIR__"changlang2",
                "north" :  __DIR__"zhengting",
        ]));
        /*
        set("objects",([
                __DIR__"npc/shanzheng" : 1,
        ]));
        */
        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
