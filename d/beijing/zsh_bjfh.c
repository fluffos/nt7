//zsh_bjfh.c
#include <ansi.h>

inherit ROOM;

#define PLACE "bje"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", MAG"紫衫会大厅"NOR);
        set("long", @LONG
这里是紫衫会设在北京的分会，大厅里挂满了各种字画，一股书
香气息迎面扑来。厅中一青年男子手捧一书籍，正漫步而吟。房间墙
壁上有一块牌子(paizi)。凡紫衫会成员均可以在这里取得各种任务去
完成。
LONG );

        set("objects", ([ 
               "/d/beijing/npc/zsh_duan"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "north" : "/d/beijing/zsh_bjdamen",
        ]));

	set("coor/x", -2770);
	set("coor/y", 7630);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>