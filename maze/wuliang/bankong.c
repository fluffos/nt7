// bankong.c
// bbb 1997/6/11
// Modify By River 98/12
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", "半空");
	set("long", @LONG
你吓出一身冷汗，不管全身的疼痛，伸出手牢牢抱住古松的树枝，登时挂
在半空，不住摇晃，向下望去，只见深谷中云雾弥漫，还是不见尽头，周围只
有树枝在不停的摇晃。下面是悬崖，再往下掉看来危险万分。
LONG
	);
        set("outdoors", "大理");
	setup();
}

void init()
{
        add_action("do_move", "pa");
        add_action("do_move", "climb");
        add_action("do_move", "move");
        add_action("do_down", "down");
}

int do_down(string arg)
{
	object me;
 	me = this_player();
	message_vision(HIR "$N松开双手，身子立即急速向下坠去，耳边风声呼呼。\n" NOR, me);
        me->unconcious();
        me->move("/d/dali/shanlu3");
	return 1;
}

int do_move(string arg)
{
	object me = this_player();
        if ( !arg || arg!="yabi") return 0;
        message_vision("$N小心地攀住树枝，向崖壁爬去。\n" , me);
        me->move(__DIR__"shushang");
        return 1; 
}