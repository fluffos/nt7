// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "刺藤树丛");
        set("long", @LONG
你走了一阵，前面出现一片无法通过的密林，这林子好不古怪，每株
树上生满了长藤钩刺，难以落脚。走不了两步，就被长藤缠住，放眼远望，
前面刺藤树密密层层，不知道能不能走出去。
LONG );
         set("exits", ([
                "west"  : __DIR__"shulin2",
                "east"  : __DIR__"beach",
                "north" : __DIR__"shanlu1",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9030);
        set("coor/y", -3000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}