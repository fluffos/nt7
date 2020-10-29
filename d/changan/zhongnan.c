//  Room:  /d/changan/zhongnan.c
#include <room.h>

inherit BUNCH_ROOM; 

void  create  ()
{
        set  ("short",  "终南山口");
        set  ("long",  @LONG
终南山又称太乙山，距长安城八十多里，素有“锦秀巨屏拱长安”
之说。据传老子曾在山中讲经。这条大官道穿越终南山口，两面秀峰入
云，这里却没有一条路可以上山。西面是往长安的大道，东面前往中原。
LONG);
        set("exits",  ([  /*  sizeof()  ==  4  */
            "east"  :  __DIR__"road2",
            "west"  :  __DIR__"road3",
            "north"  :  __DIR__"questroom",
        ]));
        set("outdoors", "guanzhong");

        set("no_clean_up", 0);
        set("coor/x", -10630);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
}
