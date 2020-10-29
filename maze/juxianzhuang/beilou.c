// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "北楼");
        set("long",  @LONG
这是游府的北楼，与南楼遥遥相对。这次英雄宴的主宾，“阎王敌”
薛神医在外厅被众多江湖豪杰争相结纳，应酬得累了，暂时到这间厢房
来歇息片刻。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"  :  __DIR__"xiaofotang",
                "east"  :  __DIR__"changlang1",
                "south" :  __DIR__"zhengting",
        ]));
        set("objects",([
                "/maze/juxianzhuang/npc/xuemuhua" : 1,
        ]));
        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
