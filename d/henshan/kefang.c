#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "衡山派客房");
        set("long", @LONG
这是一间很大的客房，是衡山派供前来祭神的游客暂住的房间陈
设十分简陋。 靠墙放了十几张小木床。 虽然简陋了点但是总比在荒
山中露宿强得多了。
LONG );
        set("sleep_room", 1);
        set("no_fight", 1);
        set("exits", ([
               "south" : __DIR__"changlang",
        ]));
	set("coor/x", -6920);
	set("coor/y", -5480);
	set("coor/z", 40);
	setup();
        replace_program(ROOM);
}