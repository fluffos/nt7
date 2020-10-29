#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","金水桥");
        set("long", @LONG
一座不大的拱桥，横架在紫禁城的护城河两岸，通过金水桥向北
走便是紫禁城的正门了，那里守卫森严，坚实的城墙高高的耸立着。
桥的南面是著名的天安门广场，在这便可以听见嘈杂的人声，过往穿
梭其中的人们络绎不绝，热闹非凡。
LONG );
        set("exits", ([
                "south" : "/d/beijing/tiananmen",
                "north" : "/d/beijing/hgmen_s",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing1" : 2,
                "/d/beijing/npc/xiaofan" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}