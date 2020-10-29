// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "小佛堂");
        set("long",  @LONG
游氏兄弟并非出身佛门，却也在家中盖了一座小佛堂，供奉佛祖和菩
萨。这次广开英雄宴，少林寺玄寂大师率弟子前来赴会，正好暂居于
此。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"  :  __DIR__"changlang3",
                "east"  :  __DIR__"beilou",
                "south" :  __DIR__"huayuan",
        ]));
        /*
        set("objects",([
                __DIR__"npc/xunji" : 1,
                __DIR__"npc/xunnan" : 1,
                __DIR__"npc/sengren" : 1,
        ]));
        */
        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
