#include <room.h>
inherit ROOM;

void create()
{
        set("short", "地西大街");
        set("long", @LONG
这里是北京城地安门的西街。街道是整整齐齐的杨树林，道上行
人络绎不绝，车辆马匹穿插其中。大街上有闲逛的游人，上京赶考的
考生，背负着担子的挑夫以及正在玩耍着的幼童构出了一幅繁忙热闹
的盛世景象。北方是一座富丽堂皇的巨宅，那就是当朝第一大臣，被
御封为『满洲第一勇士』的鳌狠的府邸。向南经过西单北大街可以通
往西单。西方接西四北大街。
LONG );
       set("exits", ([
                "north" : "/d/beijing/aofu_men",
                "south" : "/d/beijing/di_3",
                "east" : "/d/beijing/di_5",
                "west" : "/d/beijing/shi_3",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}