// Room: banshan2.c
// bbb 1997/06/11
// Modify By River 98/12
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "半山");
	set("long", @LONG
这山崖似乎无穷无尽，幸好崖缝中有不少砂石，不至于一溜而下，越到底
越是平缓，不再是危崖笔立，但耳中轰隆轰隆的声音越来越响，只觉水珠如下
大雨溅到脸上，隐隐生疼。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
	    "down" : __DIR__"banshan4",
        ]));
	set("no_clean_up", 0);
        set("outdoors", "大理");

	setup();
}

void init()
{	
	add_action("do_down", "pa");
}

int do_down(string arg)
{
	object me = this_player();
        if (!arg || arg!="down") return 0;
	message_vision(HIR "$N伏在坡上，半滚半爬，一下子溜到了谷底。\n" NOR, me);
	me->move(__DIR__"gudi");
	return 1;
}