#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地东大街");
        set("long", @LONG
这里是北京城地安门的东街。街道是整整齐齐的杨树林，道上行
人络绎不绝，车辆马匹穿插其中。大街上有闲逛的游人，上京赶考的
考生，背负着担子的挑夫以及正在玩耍着的幼童构出了一幅繁忙热闹
的盛世景象。北边是京城国子监的所在地。南边是地安门的东街广场。
LONG );
       set("exits", ([
                "north" : "/d/beijing/guozijian",
                "south" : "/d/beijing/di_donggc",
                "east" : "/d/beijing/dong_3",
                "west" : "/d/beijing/di_dajie1",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing2" : 1,
                "/d/beijing/npc/taijian" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}