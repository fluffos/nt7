// /u/cool/tls/wanfodong2.c
// cool 1998.2.13
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "万佛洞");
	set("long", @LONG
阳光被外面的树林遮住，这洞内显得较昏暗，洞内满是精美的佛
像，墙上绘着佛祖的一生事迹的故事。走在洞里，你看着墙上的壁画，
感悟颇深。这里没有什么明显的出口。
LONG);
	set("exits", ([
	       "out" : __DIR__"wfd",
	       "north" : __DIR__"wfd3",

        ]));
        create_door("north", "石门", "south", DOOR_CLOSED);

	setup();
}

void init()
{
        add_action("do_linghui","领会");
        add_action("do_linghui","linghui");	
}

int do_linghui()
{
	object me = this_player();
	message_vision("$N盘腿静坐了下来，看着眼前的壁画，良久，似有所悟。\n", me);
	me->set_busy(10);
//    me->set("shen",0);
	return 1;
}

