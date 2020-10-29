// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "海船");
        set("long", @LONG
一艘海船，大概能载十七、八个人。几名健硕的水手正在船头船尾忙
来忙去。
LONG );

        set("valid_startroom", 1);
        set("outdoors", "taohua");
        set("cost", 2);
        setup();
        replace_program(ROOM);
}


