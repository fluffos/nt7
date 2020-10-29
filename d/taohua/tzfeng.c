// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

int do_tanzhi();
void create()
{
        set("short", "弹指峰");
        set("long", @LONG
这里是整个桃花岛的最高点，居高临下，全岛景观尽收眼底。南边是
海，向西是一些光秃秃的岩石，东面北面都是花树，五色缤纷，不见尽头，
只看得人头昏眼花。峰顶有一块石碑，上有三个大字“弹指峰”，碑旁有
一个石洞。洞口之上三个大篆，虽然已磨损不少，但仍依稀可辨。细看之
下原来是“清音洞”三字。
LONG );
         set("exits", ([
                "enter" : __DIR__"qingyin",
                "southdown" : __DIR__"shanlu2",
        ]));
        
        set("objects", ([
                __DIR__"obj/taoshu" : 1,
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9030);
        set("coor/y", -2970);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
