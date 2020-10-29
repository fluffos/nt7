#include <ansi.h>

inherit ROOM;

#define PLACE "dl"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "小刀会");
        set("long", @LONG
这里就是小刀会设在大理的分舵，这里看起来混乱无比，一只破
木箱上摆着几样粗制的赌具，地上乱扔着些鸡骨头，空气中有一股鸡
香、酒香和汗臭混杂在一起的味道。一看就知道是地痞流氓的聚集地。
侧面的墙上挂着任务牌（paizi）。
LONG );

        set("objects", ([
               "/d/dali/npc/boss-long"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "up" : "/d/dali/baiyiminju",
        ]));

        setup();
}
#include <bang_bad.h>
