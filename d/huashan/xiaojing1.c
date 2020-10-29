// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "后山小径");
        set("long", @LONG
这是华山后山的一条小径，人迹鲜至。两旁野草生得密密麻麻，
要不是有人带领，谁也想不到这里竟然有条小径。
LONG );

        set("outdoors", "huashan");

        set("exits", ([ /* sizeof() == 1 */
                  "north":__DIR__"taogu",
        ]));

        setup();
        replace_program(ROOM);
}
 