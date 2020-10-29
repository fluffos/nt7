// 草堂 caotang.c
 
#include <ansi.h>
#include <room.h>

inherit ROOM;

void create() 
{ 
        set("short", "草堂");
        set("long", @LONG
这是一个草堂，由于光线充足，显得很明亮，草堂正中有一个檀
木桌，桌下面整齐地摆放着四个凳子。正门正对的墙上挂着一幅画，
画中是一个神清骨秀的中年人，左右有一副对联，画的正下方有个香
案，上面的香炉中插着几根檀香，正冉冉地燃着。正对侧面有一扇竹
门(door)虚掩着。
LONG );

        set("no_clean_up", 0);

        set("exits", ([ 
            "enter" : __DIR__"xfang4",
            "west" : __DIR__"chufang",
            "south" : __DIR__"maowu",
            "east" : __DIR__"xfang3",
        ]));

        set("objects",([
            __DIR__"npc/xtong1" : 1,
        ]));

        create_door("enter", "竹门", "out", DOOR_CLOSED);
        setup();
}