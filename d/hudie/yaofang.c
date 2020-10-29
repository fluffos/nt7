// 药房 yaofang.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "药房");
        set("long", @LONG
这里是胡青牛的药房，靠墙边都是一排一排的药柜，每个药柜上
都有一张白纸，上面写满了对药材的注释。屋的正中央，有一个小炉
子，一个小童正蹲在炉子旁，拿着一把扇子，不停地煽着火，整个屋
子一股中药的气息。南北听起来都很安静。
LONG );

        set("exits", ([
            "north" : __DIR__"xfang3",
            "west" : __DIR__"maowu",
            "south" : __DIR__"xfang1",
        ]));

        set("objects",([
            __DIR__"npc/xtong2" : 1,
        ]));

        setup();
}