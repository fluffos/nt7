#include <ansi.h>

inherit ROOM;

#define PLACE "cd"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "侠义盟成都分舵");
        set("long", @LONG
这里是侠义盟的的成都分舵，侠义盟这几年名声雀起，一方面成
大当家严厉帮规，另一方面也与各个分舵主的费心操劳是分不开的，
此间的舵主正是成总瓢把子的结拜义弟，人称蜀都大侠的洪义。侧面
的墙上挂着任务牌（paizi）。
LONG );

        set("objects", ([
               __DIR__"npc/boss-hong"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "west" : __DIR__"xym_cdfb",
        ]));

        set("coor/x", -15180);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>