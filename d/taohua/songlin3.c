// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "松柏林");
        set("long", @LONG
这座松柏林每株树木之间错落有致，枝条交互掩映，抬头望去，松针
柏叶密密重重，遮云蔽日，但林中却光线充足，纤毫毕现。真不知是天然
生就，还是妙手偶得。林中一条小径斗折蛇行，指向北方。东北面似乎有
一排竹林。
LONG );
         set("exits", ([
                "north" : __DIR__"hanbi",
                "south" : __DIR__"songlin2",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8980);
        set("coor/y", -2980);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}