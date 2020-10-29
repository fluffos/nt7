// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "绿竹林");
        set("long", @LONG
竹林全是由绿色方竹构成，林内有座竹枝搭成的凉亭，亭上横额写着
“积翠亭”三字。亭中竹几竹椅全是多年之物，用得润了，现出淡淡黄光。
竹亭之侧并肩生着两棵大树，枝干虬盘，只怕已是数百年的古树。苍桦翠
竹，清幽无比。
LONG );
        set("exits", ([
                "east"  : __DIR__"zhulin3",
                "south" : __DIR__"zhulin",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8990);
        set("coor/y", -2970);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}