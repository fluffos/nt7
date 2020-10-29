#include <ansi.h>

inherit ROOM;

#define PLACE "ca"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "侠义盟长安总舵");
        set("long", @LONG
这里是侠义盟在长安的总部大厅。这里没什么豪华的装饰，一切
清新素朴。正厅上方高高的悬挂着一块大匾上书侠之大者四个金煌煌
的大字。匾下的太师椅上端坐着一位威严的中年男子，想必就是成中
岳，成大当家。他与郭靖一样都是令世人景仰的大侠。墙上挂着一个
任务牌(paizi)，你可以在这里领到各种任务。
LONG );

        set("objects", ([
               __DIR__"npc/boss-cheng"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "south" : __DIR__"xym_zb",
        ]));

        set("coor/x", -10690);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>