#include <room.h>
inherit ROOM;

void create()
{
        set("short", "北厅");
        set("long", @LONG
这里是回春堂的帐房，帐房先生正坐在门边的一张桌子后面。由于
回春堂生意兴隆，药王谷的弟子已经忙不过来，所以大量雇佣零工伙计，
工钱不低的。如果手头缺钱或是想学习医药学，不妨在这里打打工。
LONG );
        set("no_fight", 1);
        set("exits", ([
                "west" : __DIR__"xiuxi",
                "south" : __DIR__"tingyuan",
        ]));
        set("objects", ([
                __DIR__"npc/zhangfang" : 1,
        ]));
        create_door("west", "木门", "east", DOOR_CLOSED);
        setup();
}
