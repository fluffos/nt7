// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "东大街");
        set("long", @LONG
这里是东大街的尽头，向东便可到扬州城的东大门了。远处传来
官兵的吆喝声，不言而知官兵正在那里盘问来来往往的行人。北边是
一家花店，南边是个小市场。
LONG );
        set("outdoors", "city");
        set("exits", ([
                "east"  : __DIR__"dongmen",
                "west"  : __DIR__"dongdajie2",
                "south" : __DIR__"ma_damen",
                "north" : __DIR__"huadian",
        ]));

	set("coor/x", 30);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}