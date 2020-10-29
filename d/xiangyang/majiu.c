#include <room.h>
inherit TRANS_ROOM;

void create()
{
        set("short", "马厩");
        set("long", @LONG
这里是襄阳城内唯一一家车马行。你可花钱租辆马车到各个地方
去，能节约不少体力。近来因为郭夫人——黄蓉正在组织人力四处搜
集防城材料，马夫积极响应，免费提供推车来运送各种防城材料。雨
檐下钉着块木牌(paizi)。
LONG );
        set("outdoors", "xiangyang");
        set("exits", ([
                "south"  : __DIR__"northroad2",
                "up"     : "/clone/shop/xiangyang_shop",
        ]));
        set("no_fight", 1);
        set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
        ]));
        set("coor/x", -7800);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}