// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "游府正厅");
        set("long",  @LONG
这是一间颇为宽阔的厅堂，没有什么太多的装饰，只在北面墙上挂了
一幅名家所绘的《百马图》，暗合此间主人的名字。正厅当中摆了一
张红木茶几，左右各放了一张太师椅，椅上坐的二人便是这座宅院的
主人，游氏双雄。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"  :  __DIR__"huayuan",
                "east"  :  __DIR__"dayuan",
                "south" :  __DIR__"nanlou",
                "north" :  __DIR__"beilou",
        ]));
        /*
        set("objects",([
                __DIR__"npc/youju" : 1,
                __DIR__"npc/youji" : 1,
        ]));
        */
        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
