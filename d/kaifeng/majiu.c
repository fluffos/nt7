#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short", "马厩");
        set("long", @LONG
这是稻香居后的马厩，常年供应新鲜草料。开封府自古乃军事重
地，历史悠久，民风淳朴。马夫们会把马牵到马厩好生照看，将它们
喂饱饮足，再洗刷得干乾净净，一直伺候到客人上路。马厩雨檐下的
烂木柱上钉着一块破木牌 (paizi)。马厩中堆放著几堆草料，正中有
一口泔槽。
LONG );
        set("outdoors", "kaifeng");
        set("no_fight", 1);
        set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
        ]));
        set("exits",([
               "west" : __DIR__"daoxiang",
               "north" : __DIR__"business",
               "up"   : "/clone/shop/kaifeng_shop",
        ]));
	set("coor/x", -5030);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}