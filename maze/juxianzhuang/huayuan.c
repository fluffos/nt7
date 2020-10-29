// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short", "花园");
        set("long", @LONG
这里是游府的花园。院子里种了各色名贵的牡丹。
LONG );
        set("outdoors", "luoyang");
        set("region", "luoyang");

        set("exits", ([
                "north" : __DIR__"xiaofotang",
                "south" : __DIR__"xiangfang1",
                "west"  : __DIR__"yanwuchang",
                "east"  : __DIR__"zhengting",
        ]));

        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"
