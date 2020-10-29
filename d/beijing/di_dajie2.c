#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地安门大街");
        set("long", @LONG
这里是北京城的地安门大街。街道是整整齐齐的杨树林，道上行
人络绎不绝，车辆马匹穿插其中。大街上有闲逛的游人，上京赶考的
考生，背负着担子的挑夫以及正在玩耍着的幼童构出了一幅繁忙热闹
的盛世景象。北边过地安门到达京城的城郊，南边是热闹的地安门广
场。
LONG );
       set("exits", ([
                "north" : "/d/beijing/di_anmen",
                "south" : "/d/beijing/di_dajie1",
        ]));
        set("objects", ([
                "/d/beijing/npc/dipi" : 1,
                "/d/beijing/npc/tiaofu" : 2,
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}