// dongkou.c
// bbb 1997/06/11
// Modify By River 98/12
#include <ansi.h>
inherit ROOM;

string look_huan();
void create()
{
	set("short", "洞口");
	set("long", @LONG
走得十余步，洞中已无丝毫光亮，但觉脚下平整，便似走在石板路上一样，
洞中道路必是经过人工修整，只是道路不住的向下倾斜，显是越走越低突然之
间，你碰到什么，有圆物铛的一下，声音清亮，原来是个门环(huan)
LONG
	);
        set("exits", ([
		"out" : __DIR__"shibi",
        ]));
        set("outdoors", "大理");
	set("item_desc", ([
             "huan" : "门环在一扇大门上，似以钢铁铸成，但里面并未插上。\n",
	]));

	setup();
}

void init()
{
        add_action("do_knock", "knock");
        add_action("do_knock", "qiao");
        add_action("do_enter", "push");
        add_action("do_enter", "tui");
}

int do_knock(string arg)
{
	object me;
 	me = this_player();
        if (!arg ||arg!="huan") return 0;
	message_vision("$N提起门环当的敲了一下，但门内无人答应。\n" , me);
        set_temp("knock_door", 1, me);
	return 1;
}

int do_enter(string arg)
{
	object me = this_player();
        if (!arg ||arg!="huan") return 0;
        if( query_temp("knock_door", me)){
        message_vision("$N手劲使将上去，那门便缓缓的开了。\n"  , me);
	set("exits/enter", __DIR__"dong1");
        return 1; 
        }
      return notify_fail("就这样贸然闯入不太好吧。\n");
}