//hbd_cafb.c
#include <ansi.h>

inherit ROOM;

#define PLACE "ca"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", HIB"黑白道长安分坛"NOR);
        set("long", @LONG
这里就是黑帮组织黑白道的长安分坛了。墙壁是奇特的黑白两色。
房间正中的台子上摆着一把剑一把刀，可以看出此处的分坛主必定是
个痴迷武学之人。墙上挂着一个牌子（paizi）。
LONG );

        set("objects", ([ 
               __DIR__"npc/hbd_chengwu"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "out"   :  __DIR__"miao",
        ]));

        setup();
}
#include <bang_bad.h>
