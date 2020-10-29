#include <room.h>
inherit ROOM;

void create()
{
        set("short", "高升茶馆");
        set("long", @LONG
一座规模不小的茶馆，门前的幡上舞着『高升』两个大字。你刚
进来，就闻到一股茶香沁入心脾，精神为之一爽。几张八仙桌一字排
开，坐满了客人，或高声谈笑，或交头接耳。茶博士摇头晃脑的说着
书，茶铺的伙计忙个不停。你要想打听江湖掌故和谣言，这里是个好
所在。
LONG );
       set("exits", ([
                "north" : "/d/beijing/caroad_w2",
        ]));
        set("objects", ([
                "/d/beijing/npc/chaboshi" : 1,
                "/d/beijing/npc/teahuoji" : 1,
                "/d/beijing/npc/chake" : 2,
                "/d/beijing/npc/old2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}