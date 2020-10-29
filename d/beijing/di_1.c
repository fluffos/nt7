#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地西大街");
        set("long", @LONG
这里是北京城地安门的西街。街道是整整齐齐的杨树林，道上行
人络绎不绝，车辆马匹穿插其中。大街上有闲逛的游人，上京赶考的
考生，背负着担子的挑夫以及正在玩耍着的幼童构出了一幅繁忙热闹
的盛世景象。从这里一直往北可以到达当朝第一大臣鳌狠的府邸。向
南经过西单北大街可以通往西单。
LONG );
       set("exits", ([
                "north" : "/d/beijing/di_3",
                "east" : "/d/beijing/di_2",
                "south" : "/d/beijing/bei_4",
        ]));
        set("objects", ([
                "/d/beijing/npc/youren" : 1,
                "/d/beijing/npc/shusheng2" : 1,
                "/d/beijing/npc/kid1" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}