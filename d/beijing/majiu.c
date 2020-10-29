#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short", "马厩");
        set("long", @LONG
这是北京城的马厩，常年供应新鲜草料。北京自古天子脚下，啥
都有规矩，客店也特会伺候人，马夫们会把马牵到马厩好生照看，将
它们喂饱饮足，再洗刷得干乾净净，一直伺候到客人上路。雨檐下的
烂木柱上钉着块破木牌 (paizi)。马厩中堆放著几堆草料，正中有一
口泔槽。
LONG );
        set("outdoors", "beijing");
        set("no_fight", 1);
        set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
                "/d/guanwai/npc/shenke" : 1,
        ]));

        set("exits",([
                "east" : __DIR__"niaoshi",
                "north"  : __DIR__"business",
                "up"   : "/clone/shop/beijing_shop",
        ]));
	set("coor/x", -2850);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}