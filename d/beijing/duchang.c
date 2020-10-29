#include <room.h>
inherit ROOM;

void create()
{
        set("short", "宏升赌场");
        set("long", @LONG
这里就是北京城中最大的宏升赌场，四周的赌房里传出来吆五喝
六的赌博声。这个赌场规模虽算不上很大， 但赌的种类却很齐全， 
服务也非常周到。在这儿， 世上的各行各色的人夹杂在一起， 有腰
盘万贯的富家子弟， 也有穷得叮当响的穷汉。有拿刀佩剑的的江湖侠
客， 也有掉儿啷当的流氓地痞。有官府的侍卫， 也有在逃的犯人。
LONG );
       set("exits", ([
                "south" : "/d/beijing/yong_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/duke" : 2,
                "/d/beijing/npc/liumang" : 1,
                "/d/beijing/npc/haoke1" : 1,
                "/d/beijing/npc/dipi" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}