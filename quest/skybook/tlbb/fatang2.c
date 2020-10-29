// Room: fatang2.c
// tangfeng@SJ 2004

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", "法堂二楼");
	set("long", @LONG
这里是大轮寺掌门居所，四面清幽，修禅证道最妙不过。真是：
    戏招西塞山前月，来听东林寺里钟。
    悠然万虑忘，有此一楼足。
    西窗外，群山万壑，望尽天地。
    东窗外，楼台错落，几尽悠闲。
LONG
	);

	set("exits", (["down" : __DIR__"fatang",]));
        set("objects", ([CLASS_D("xueshan") + "/jiumozhi" : 1,]));
	setup();
}
void init()
{
        add_action("do_push", "push");
        add_action("do_look", "look");
}
int do_look(string arg)
{
	object me = this_player();

	if (!me->query_temp("quest/天龙八部/天龙营救篇/askzhi")) {
		set("long", @LONG
这里是大轮寺掌门居所，四面清幽，修禅证道最妙不过。真是：
    戏招西塞山前月，来听东林寺里钟。
    悠然万虑忘，有此一楼足。
    西窗外，群山万壑，望尽天地。
    东窗外，楼台错落，几尽悠闲。
LONG
);
		me->look(arg);
	}
	else {
		if (!arg) {
			set("long", @LONG
这里是大轮寺掌门居所，四面清幽，修禅证道最妙不过。真是：
    戏招西塞山前月，来听东林寺里钟。
    悠然万虑忘，有此一楼足。
    西窗外，群山万壑，望尽天地。
    东窗外，楼台错落，几尽悠闲。
    
只是你仔细地观察着四周，发现北面墙边（wall）似乎隐有活动。
LONG
);
			me->look(arg);
		}
		else if (arg == "wall") {
			tell_object(me,HIR"你仔细地观察着四周，发现墙边可以推开（push）。\n"NOR);
			return 1;
		}
 }		
}

int do_push(string arg)
{
		object me = this_player();
    if (!me->query_temp("quest/天龙八部/天龙营救篇/askzhi")) return 0;
	      if( arg == "wall" || arg == "墙" || arg == "墙边")
        {
        message_vision("$N推开这堵墙，发现了向北通向一个暗室。\n", this_player());
        if( !query("exits/north") ) {
        set("exits/north", __DIR__"anshi");
        remove_call_out("close_path");
        call_out("close_path", 15);
        }
        return 1;
        }
}
void close_path()
{
        if( !query("exits/north") ) return;
        message("vision","一会会，嗵的一声，墙又恢复原样。\n", this_object() );
        delete("exits/north");
}
int valid_leave(object me, string dir)
{
     if (dir == "north" && present("jiumo zhi", environment(me)))
     return notify_fail("鸠摩智喝道：乱走什么，这位大师请回！\n");    
     if (dir == "north" && me->query_condition("killer"))
     return notify_fail("你发现似乎有股神力维护那里，你无法进入！\n");
     return ::valid_leave(me, dir);
}
