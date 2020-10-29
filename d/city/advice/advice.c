#include <ansi.h>
inherit ROOM;
int is_chat_room()      { return 1;}
void create()
{
       set("short", HIY "游戏客服" NOR);
        set("long", @LONG
大家对游戏种遇到的问题及游戏发展的意见都可以POST在这里！
谢谢大家合作。
LONG );

        set("exits", ([
                "out" : "/d/city/kedian4",
                "sea" : "/inherit/room/hanghai_room.c",
                "up"  : "/adm/daemons/fairyland_quest/room_door_hj",
        ]));
                set("no_fight", 1);
                set("no_sleep_room",1);
	set("coor/x", 1);
	set("coor/y", 11);
	set("coor/z", 10);
	setup();
        "/clone/board/advice_b"->foo();

}
