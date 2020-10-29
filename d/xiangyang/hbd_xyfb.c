//hbd_xyfb.c
#include <ansi.h>

inherit ROOM;

#define PLACE "xy"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", HIB"黑白道襄阳分坛"NOR);
        set("long", @LONG
这里就是黑帮组织黑白道的襄阳分坛了，墙壁是奇特的黑白两色，
地上却铺着华丽的地毯，正中的太师椅上的白虎皮也显示出这里的主
人必定爱慕荣华富贵。墙上挂着个牌子（paizi）。
LONG );

        set("objects", ([ 
               __DIR__"npc/hbd_jiabj"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "out"   :  __DIR__"hutong2",
        ]));

        setup();
}
#include <bang_bad.h>
