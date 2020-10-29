// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
这是一条平缓的山路，你慢慢向上行去，山路两旁种植着松柏桦之类
的高大乔木，间杂以各种罕见药草，如灵芝、首乌之类。越往上行，山路
越见陡峭，但幸好还不算太难走。
LONG );
         set("exits", ([
                "south"   : __DIR__"citeng",
                "northup" : __DIR__"shanlu2",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9030);
        set("coor/y", -2990);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}