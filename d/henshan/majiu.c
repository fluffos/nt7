#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short","马厩");
        set("long", @LONG
这是衡阳城南的马厩，常年供应新鲜草料。衡阳地狭人稀来往行
人也很少。从这里可以乘马车到附近的城市，马厩雨檐下的烂木柱上
钉着一块破木牌(paizi)。 马厩中堆放著几堆草料，正中有一口泔槽。
LONG );
        set("outdoors", "hengyang");
        set("no_fight", 1);

        set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
        ]));

        set("exits",([
               "north" : __DIR__"hengyang11",
                "up"   : "/clone/shop/hengyang_shop",
        ]));

	set("coor/x", -6910);
	set("coor/y", -5710);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}
