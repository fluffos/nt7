#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short", HIW"小洞天"NOR);
        set("long", @LONG
你无意间闯入了一个山谷，这里幽静异常，你不由的心里有些发毛。
山谷两侧都是峭壁，南面一直通向山谷深处，这里没有什么路，灌木
树枝挡住了前进的路。西面是你进来的路
LONG);
        set("outdoors", "天龙寺");
        set("exits", ([             
               "west" : __DIR__"songlin-2",
                      ]));
set("objects",([
//        "/d/dali/npc/yetu" : 1,
		]));

        setup();
}

