//zsh_bjfh.c
#include <ansi.h>

inherit ROOM;

#define PLACE "dl"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", MAG"紫衫会大厅"NOR);
        set("long", @LONG
这里是紫衫会设在大理的分会，厅中挂了很多丹青草图，几名书
僮有的提画卷，有的磨墨。正中一白须老者，正信手挥毫，看来正在
作画。房间墙壁上有一块牌子(paizi)。凡紫衫会成员均可以在这里取
得各种任务去完成。
LONG );

        set("objects", ([ 
               "/d/dali/npc/zsh_xiao"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "north" : "/d/dali/zsh_dldamen",
        ]));

	set("coor/x", -19150);
	set("coor/y", -6910);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>