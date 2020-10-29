#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西单");
        set("long", @LONG
这里就是西单，西单也是京城里的繁华地段。人来人往，十分热
闹。从南边扬起了一阵阵马蹄声，那是京城的长安大街。西方是一个
鸟市，那是专门为江洲城里的公子哥儿开设的。北边不远就是西单北
大街了。
LONG );
       set("exits", ([
                "east" : "/d/beijing/xi_2",
                "west" : "/d/beijing/niaoshi",
                "north" : "/d/beijing/bei_1",
                "south" : "/d/beijing/caroad_w1",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy1" : 1,
                "/d/beijing/npc/tiaofu" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}