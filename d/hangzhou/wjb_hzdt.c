#include <ansi.h>

inherit ROOM;

#define PLACE "hz"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "无极帮杭州分舵");
        set("long", @LONG
这里是无极帮设在杭州的分舵，这里装饰的极为气派体面，一进
门正对着你的是一幅巨大的山水屏风画，画的正是那杭州西湖畔的美
景。大红的地毯两边，整齐的排列着两行座椅，看来这里经常讨论些
无极帮的大事。一个气质不凡的中年人，端坐在太师椅上。想必就是
无极帮杭州分舵主万剑愁万大侠了。侧面的墙上挂着任务牌（paizi）。

LONG );

        set("objects", ([
                __DIR__"npc/boss-wan"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "east" : "/d/hangzhou/wjb_hzfb",
        ]));

	set("coor/x", 810);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>