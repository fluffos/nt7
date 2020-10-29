// Room: /d/shaolin/smdian.c
// Date: YZC 96/01/19
// by zqb

inherit ROOM;
#include <ansi.h>


void init();
void close_gate();
string look_gate();
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"


void create()
{
	set("short", HIY"山门殿"NOR);
	set("long", @LONG
这里是少林寺的前殿山门殿。殿内青砖铺地，两侧分列哼、哈二将。身躯
雄伟，面相忿怒，头带宝冠，上半身裸露，手执金刚杵，一鼓鼻，一张口，露
牙睁目，凶猛可畏。两边各放一红木供桌，陈列香烛，以供僧俗叩拜。北面是
一片广场。南面是一道三丈来高的朱红杉木包铜大门(gate)。
LONG
	);

	set("exits", ([
		"north" : __DIR__"gchang-1",
	]));

	set("item_desc",([
		"gate" : (: look_gate :),
	]));
	set("objects",([
		__DIR__"npc/zn-seng" : 2,
	]));
	setup();
}

void init()
{
	add_action("do_open", "open");
	add_action("do_close", "close");
}

void close_gate()
{
	object room;

	if(!( room = find_object(__DIR__"guangchang")) )
		room = load_object(__DIR__"guangchang");
	if(objectp(room)){
		delete("exits/south");
			message("vision", "僧兵上前把大门关了起来。\n", this_object());
		room->delete("exits/north");
		message("vision", "乒地一声，里面有人把大门关上了。\n", room);
	}
}

int do_close(string arg)
{
	if (!query("exits/south"))
		return notify_fail("大门已经是关着的了。\n");

	if (!arg || (arg != "gate" && arg != "south"))
		return notify_fail("你要关什么？\n");

	message_vision("$N朝僧兵点了点头。\n", this_player());

	remove_call_out("close_gate");
	call_out("close_gate", 2);

	return 1;
}

int do_open(string arg)
{
	object room;

	if (query("exits/south"))
		return notify_fail("大门已经是开着了。\n");

	if (!arg || (arg != "gate" && arg != "south"))
		return notify_fail("你要开什么？\n");

	if(!( room = find_object(__DIR__"guangchang")) )
		room = load_object(__DIR__"guangchang");
	if(objectp(room))
	{
		set("exits/south", __DIR__"guangchang");
		message_vision("$N使劲把大门打了开来。\n", this_player());
		room->set("exits/north", __FILE__);
		message("vision", "吱地一声，里面有人把大门打开了。\n", room);
		remove_call_out("close_gate");
		call_out("close_gate", 10);
	}

	return 1;
}

string look_gate()
{
	return "一道三丈来高的朱红杉木包铜大门。\n";
}

int valid_leave(object me, string dir)
{
	if (dir == "south") {
		if (me->id("seng bing")) return 0;
		if (me->id("mo tou")) return 0;
	}
   if(dir == "south"&&!me->query_condition("killer") && me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && !me->query_temp(QUESTDIR5+"shaolinzhen"))
  {
   message_vision(HIC"\n突然刚准备离开少林寺，$N似乎气血有些不顺，跟着脚下一个趔趄。\n"NOR,me); 
   message_vision(WHT"一个执法僧匆匆了走了过来，向$N一拱手道：“我弥陀佛，施主如此凶狠，还是留在少林潜修佛法得好。”\n"NOR,me);
   me->move("/d/shaolin/shaolinzhen");
   tell_room(environment(me), HIR"\n半空中，似乎一个人掉了下来，你定眼一看竟然是"+ me->name()+ "。\n"NOR, ({ me }));
   log_file("quest/TLBB", sprintf("%s(%s)被关进少林阵。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
   return notify_fail(HIR"你疑惑了一下，却发现四周围上一圈人，似乎是少林伏魔圈阵。\n"NOR);
  }
	return ::valid_leave(me, dir);
}
