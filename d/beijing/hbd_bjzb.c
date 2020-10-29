//hbd_bjzb.c
#include <ansi.h>

inherit ROOM;

#define PLACE "bje"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", HIB"黑白道总坛"NOR);
        set("long", @LONG
这里就是黑白道北京城东总坛，这里居然是一间完全封闭的房间！
墙壁也异常的的奇怪，居然一半是黑色一半是白色，正中站着一个长
发怪人，黑白分明的身体，与周围的环境搭配在一起，给人莫名其妙
的恐惧感。房间正中的台子上放着一个黑白令旗。对面的墙上挂着任
务牌(paizi)。
LONG );

        set("objects", ([ 
               "/d/beijing/npc/boss-heibai"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "out"   : "/d/beijing/yancao",
        ]));

        setup();
}
#include <bang_bad.h>
