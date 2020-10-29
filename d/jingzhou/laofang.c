// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "监狱");
        set("long", @LONG
这是约莫两丈见方的一间大石屋，墙壁都是一块块粗糙的大石所砌，
地下也是大石块铺成，墙角落里放着一只粪桶，鼻中闻到的尽是臭气和
霉气。牢房外却可听见燕语呢喃，向燕语处望去，只见一对燕子渐飞渐
远，从数十丈外高楼畔的窗下掠过。那纱窗紧紧地关着，窗槛上却总是
供着一盆鲜花，春天是茉莉、玫瑰，夏天是丁香、凤仙。从西面墙上的
小窗望去，可以见到翰林府的一角。
LONG );

        set("exits", ([
                "west" : __DIR__"ymzhengting",
        ]));
        set("objects", ([
                __DIR__"npc/dingdian" : 1,
        ]));

        create_door("west", "铁门", "east", DOOR_CLOSED);
        set("cost", 0);
        set("coor/x", -7100);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
}