//xym_yzfb.c
#include <ansi.h>

inherit ROOM;

#define PLACE "yz"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "侠义盟扬州分舵");
        set("long", @LONG
这里是侠义盟在扬州的分舵。分舵舵主郑云虎乃成中岳麾下的一
员猛将，粗犷豪迈。在房间的墙上有一块牌子 (paizi)。加入侠义盟
的玩家，可以在这里选择任务去完成。
LONG );

        set("objects", ([
               "/d/city/npc/boss-zheng"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "south" : "/d/city/xym_yzdamen",
        ]));

	set("coor/x", -50);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>