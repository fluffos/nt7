#include <ansi.h>

inherit ROOM;

#define PLACE "bjw"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "无极帮北京西城分舵");
        set("long", @LONG
这里是无极帮设在北京的分舵，这里装饰的极为气派体面，一进
门正对着你的是一幅巨大的山水屏风画，画的正是那杭州西湖畔的美
景。大红的地毯两边，整齐的排列着两行座椅，看来这里经常讨论些
无极帮的大事。侧面的墙上挂着任务牌（paizi）。 
LONG );

        set("objects", ([
               "/d/beijing/npc/boss-zhong"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "west" : "/d/beijing/wjb_bjwfb",
        ]));

	set("coor/x", -2780);
	set("coor/y", 7620);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>