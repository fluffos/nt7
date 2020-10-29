#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地西大街");
        set("long", @LONG
这里是北京城地安门的西街。街道是整整齐齐的杨树林，道上行
人络绎不绝，车辆马匹穿插其中。大街上有闲逛的游人，上京赶考的
考生，背负着担子的挑夫以及正在玩耍着的幼童构出了一幅繁忙热闹
的盛世景象。北边是地安门西街的广场。南边警备深严，不时有官兵
进进出出，原来那里就是京城的特务机构西厂的大门所在地。
LONG );
       set("exits", ([
                "north" : "/d/beijing/di_xigc",
                "west" : "/d/beijing/di_1",
                "south" : "/d/beijing/xichang_men",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing3" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}