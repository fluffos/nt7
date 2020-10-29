// shushang.c
// bbb 1997/06/11
// Modify By River 98/12
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "树上");
	set("long", @LONG
你现在的处境还是不妙，树枝不停地发出『吱吱』的响声，随时会断你人
还是挂在半空，不住摇晃，向下望去，只见深谷中云雾弥漫，见不到尽头，看
那崖壁好象有条细缝(feng)。
LONG
	);
	set("item_desc", ([
	   "feng" : "你的脚勉强可以够到。\n"
        ]));
        set("outdoors", "大理");

	setup();
}

void init()
{
        add_action("do_move", "gou");
        add_action("do_move", "reach");
        add_action("do_down", "move");
        add_action("do_down", "pa");
}

int do_down(string arg)
{
	object me;
 	me = this_player();
	message_vision(HIR "$N继续爬向崖壁，『啊～～不好！』树枝断了，$N急速向下坠去。\n" NOR, me);
        me->unconcious();
        me->move("/d/dali/shanlu3");
	return 1;
}

int do_move(string arg)
{
	object me = this_player();
        if (!arg || arg!="feng") return 0;
        message_vision(HIR "$N小心地攀住树枝，向崖缝用脚探去，勉强攀援而下。\n"  NOR, me);
        me->move(__DIR__"banshan1");
        return 1; 
}