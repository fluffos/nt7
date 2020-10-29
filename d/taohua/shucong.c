// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "树丛");
        set("long", @LONG
这是一片花树繁密的树丛，枝叶密密重重，一眼望去，除了花树还是
花树，完全看不清对面。突然，前面约莫两丈远处一对眼睛碧莹莹的闪闪
发光。你大吃一惊，往后跳开几步，那眼睛却一闪就不见了。你有点害怕，
还是回去吧。
LONG );
        set("exits", ([
                "north" : __DIR__"shidong",
                     "east"  : __DIR__"caodi",
                "west"  : __DIR__"harbor",
        ]));

        set("objects", ([
                __DIR__"obj/taoshu" : 1,
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8980);
        set("coor/y", -3000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}