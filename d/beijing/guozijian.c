#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "国子监");
        set("long", @LONG
这里就是京城的国子监。国子监是朝廷培养人才的地方。高高低
低的桌子排了两排。在这里不时可以看到三三两两的学生模样的人大
声争辩着什么问题，还有一些老先生们蹙着眉头匆匆的走过，象是在
思考着什么问题。[2；37；0m
LONG );
        set("exits", ([
                "south" : "/d/beijing/dong_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/shusheng1" : 3,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}