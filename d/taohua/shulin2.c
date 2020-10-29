// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "树林");
        set("long", @LONG
这是一片普通树林，与岛上一入就迷失方向的桃林不大一样。林中一
条小路横贯东西。东北面地势越来越高，似乎有座山峰；往东走树林愈现
茂密，看来不太好走。
LONG );
         set("exits", ([
                "west" : __DIR__"shulin",
                "east" : __DIR__"citeng",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9020);
        set("coor/y", -3000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}