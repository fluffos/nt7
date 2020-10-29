// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "厢房");
        set("long",  @LONG
这里是游府的一间厢房，游氏双雄的知交好友来府上做客大多居于此
处。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"  :  __DIR__"changlang7",
                "south" :  __DIR__"xiangfang2",
        ]));

        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
