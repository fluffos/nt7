#include <ansi.h>
inherit ROOM;
int do_knock(string arg);

void create()
{
	set("short", "钟楼");
	set("long", @LONG
这是一座砖木结构的小楼，飞檐翘翎，檐角上挂满了一串串小铜铃，随风
叮叮作响。墙上镂空雕绘着无数佛陀们的坐像。一个个形态维肖。楼内高悬者
一个大钟(zhong)，看样子不下上千斤，钟身上铸有金刚经文，这钟一旦敲响，
在大理城内都可闻见。
LONG
        );

	set("exits", ([
		"east" : __DIR__"road1",
		"south"  : __DIR__"zt1",
		"north"  : __DIR__"dizangdian",
	]));

	set("item_desc",([
		"zhong"		:	"这口钟很大，每天都有人来敲(qiao)的",
	]));

	set("objects",([
		__DIR__"npc/guest" : 1,
	]));

	set("outdoors", "天龙寺");
	setup();
}

void init()
{
	add_action("do_knock", "knock");
	add_action("do_knock", "qiao");
}

int do_knock(string arg)
{       
	mixed *local;
	object me;
	int costj, costq;
	me = this_player();

	local = localtime(time() * 60);
	            
	if (me->is_busy()) {
		write("你现在正忙着呢!\n");
		return 1;
	}

	if (me->is_fighting()) {
		write("你正在战斗中,无法专心干活!\n");
		return 1;
	}
          
	if (!( present("zhong chui", this_player())))
		return notify_fail("你试了下，显然用手是撞不响钟的。\n");

	if ( !arg || arg != "zhong" ) {
		write("你要撞什么？\n");
		return 1;
	}
        
	if (local[2] < 6 || local[2] >= 21) {
		message_vision("『咣……』的一声,一个小和尚突然外面跑过来说：“现在是休息时间，请毋敲钟！”\n"+
				"小和尚见$N放下钟锤，打了个哈乞，走了出去。\n",me);
		return 1;
	}

	costj = (int)me->query("con")/3;
	costq = (int)me->query("str")/2;

	if ((int)me->query("jingli") < costj || (int)me->query("qi") < costq) {
		message_vision("钟声一响，$N被巨大的轰鸣声震的昏了过去。\n",me);
		me->unconcious();
		return 1;
	}
	if ((int)me->query_skill("force",1) < 30 ) {
		message_vision("『咣……』的一声，$N被震的昏了过去。\n",me);
		me->unconcious();
		return 1;
	}          
	me->receive_damage("jingli", costj);
	me->add("qi", -costq);       

	message_vision("$N敲了一下大钟，『咣……』声音传遍整个寺庙。\n", me);
		
	if ((int)me->query_skill("force", 1) < 101 ) {
		write("钟声震得你眼前发晕，你深吸了一口气，暗运内功抵挡。\n");
		me->improve_skill("force", (int)me->query_int()/2);
	}
	else {
		write("钟声响起，你不由的心中暗起肃穆之心。\n");
	}
	return 1;
}
