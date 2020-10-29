#include <ansi.h>
#include <room.h>
#include <wanted.h>
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
#define TIME_TICK (time()*60)

inherit ROOM;

void create()
{
	set("short", "山路");
	set("long", @LONG
你信步而行，举步踏到的尽是矮树长草，这里没有路,每走一步，荆棘都
钩刺到小腿,划破你的身体。
LONG
        );
	set("outdoors", "大理");

	set("exits", ([
		"south" : __DIR__"shanlu11",
		"north" : __DIR__"shanlu11",
		"west" : __DIR__"shanlu11",
		"east" : __DIR__"shanlu11",
	]));

	setup();
}

void init()
{
	object me = this_player();

	if( query(QUESTDIR1+"pass_shanlu", me )
	 && me->query_skill("lingbo-weibu", 1) < 140
	 && ! is_wanted(me)){
		me->move("/maze/wuliang/gaoshan", 1);
		message_vision(HIR"$N熟悉地绕过森林，来到一个高山上。\n"NOR, me);
	}
	if( random(query("kar", me))<10 && me->query_con()<30){
set_temp("last_damage_from", "在森林里筋疲力尽累", 		me);
addn("qi", -30, 		me);
addn("jingli", -10, 		me);
		me->receive_wound("jing", 20);
	}
	else {
addn("qi", -20, 		me);
	}
	add_action("do_look", "look");
}

int do_look()
{
	object me = this_player();
	mixed *local;
	local = localtime(TIME_TICK);
	if(local[2] < 6 &&random(6)<2) {
	message("vision",BLU"天黑了,这里黑黝黝一片，伸手不见五指,你四处乱走着,心里充满恐惧.\n"
				"突然传来几声野兽的嚎叫,你吓的哭了起来.\n"NOR, me);
	}
}
int valid_leave(object me, string dir)
{
	mixed *local;
	int i = 0;

	local = localtime(TIME_TICK);

	if (dir == "west")
addn_temp("mark/steps", 1, 		me);
	if (dir == "south")
addn_temp("mark/step", -1, 		me);
	if (dir == "east")
addn_temp("mark/steps", -1, 		me);
	if (dir == "north")
addn_temp("mark/step", 1, 		me);

/**for 营救段誉 ***/
// Modify By River 关于不能太简单获得 lbwb ，只给三次机会 

// Modify By tangfeng Quest本身谁可以解的，问题是拿到帛卷是否领悟到凌波微步

	if( query_temp("mark/steps", me) == query_temp(QUESTDIR1+"steps", me )
	 && query_temp("mark/step", me) == query_temp(QUESTDIR1+"step", me) )
		i = 1;
	if( wizardp(me))  tell_object(me,HIR"\ni="+i+".\n"NOR);
	if (i
		&& local[2] < 6
		 && query_temp(QUESTDIR1+"yingjiu", me )
		&& !me->query_condition("killer"))
	{
		me->move("/maze/wuliang/gaoshan");
set(QUESTDIR1+"pass_shanlu", 1, 		me);
delete_temp("mark/steps", 		me);
delete_temp("mark/step", 		me);
		return notify_fail(HIR"\n你走到了一个高山上。\n"NOR);
	}
	if( (query_temp("mark/steps", me)<-10
	 || query_temp("mark/step", me)<-10
 	 || query_temp("mark/steps", me)>12
	 || query_temp("mark/step", me)>12) && !random(20) )
	{
		if( query_temp(QUESTDIR1+"yingjiu", me))set("quest/天龙八部/time", time(), me);
		me->move("/maze/wuliang/xiaoxi");
delete_temp("mark/steps", 		me);
delete_temp("mark/step", 		me);
		if( query_temp(QUESTDIR1+"yingjiu", me)){
delete_temp("quest/天龙八部", 			me);
			me->delete_temp("quest/busy");//任务冲突标志取消
			return notify_fail(HIW"\n你筋疲力尽地走出这段山路，沮丧地发现自己怎么也找不到四大恶人的行踪。\n"NOR);
		}
		else return notify_fail(HIY"你筋疲力尽，终于走出了这段山路。\n"NOR);
	}
	return ::valid_leave(me, dir);
}
/*
int valid_leave(object me, string dir)
{
	mixed *local;
	int i = 0;

	local = localtime(TIME_TICK);

	if (dir == "west")
addn_temp("mark/steps", 1, 		me);
	if (dir == "south")
addn_temp("mark/step", -1, 		me);
	if (dir == "east")
addn_temp("mark/steps", -1, 		me);
	if (dir == "north")
addn_temp("mark/step", 1, 		me);

	if( query_temp("mark/steps", me) == query_temp("duanyu/steps", me )
	 && query_temp("mark/step", me) == query_temp("duanyu/step", me) )
		i = 1;
	if (i
	 && (random(query("kar", me))+random(query("int", me)))>50
	 && (random(me->query_con(1))+random(me->query_int(1))) > 75
	 && local[2] < 6 
	 && local[2] >= 3
	 && query_temp("duanyu/find2", me)){
		me->move(__DIR__"gaoshan");
		log_file("quest/lbwb",
			sprintf("%-18s顺利通过山路，走上寻找凌波微步之路，福：%d，悟：%d，根：%d，悟：%d。\n",
				me->name(1)+"("+capitalize(getuid(me))+")", 
query("kar", 				me),
query("int", 				me),
				me->query_con(1),
				me->query_int(1)
			), me
		);
set("quest/dali/shanlu", 1, 		me);
delete_temp("mark/steps", 		me);
delete_temp("mark/step", 		me);
		return notify_fail("你走到了一个高山上。\n");
	}
	if( query_temp("mark/steps", me)<-8
	 || query_temp("mark/step", me)<-8
 	 || query_temp("mark/steps", me)>10
	 || query_temp("mark/step", me)>10
	 || i && !random(30)) {
		if( query_temp("duanyu/find2", me)){
addn("quest/dali/fail", 1, 			me);
set("quest/dali/time", time(), 			me);
			log_file("quest/lbwb",
				sprintf("%-18s第%d次机会没有掌握，未能顺利通过山路。\n",
					me->name(1)+"("+capitalize(getuid(me))+")", 
query("quest/dali/fail", 					me )
				), 
			me);
		}
		me->move(__DIR__"xiaoxi");
delete_temp("mark/steps", 		me);
delete_temp("mark/step", 		me);
		if( query_temp("duanyu/find2", me)){
delete_temp("duanyu", 			me);
			return notify_fail(HIW"\n你筋疲力尽地走出这段山路，沮丧地发现自己怎么也找不到四大恶人的行踪。\n"NOR);
		}
		else {
delete_temp("duanyu", 			me);
			return notify_fail("你筋疲力尽，终于走出了这段山路。\n");
		}
	}
	return ::valid_leave(me, dir);
}
*/