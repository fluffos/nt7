// sheshenya.c
// 舍身崖

// Modified by mxzhao 2004/04/11 for do_jump function

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short",MAG "睹光台舍身崖" NOR);
	set("long",@long
从卧云庵出来，这里是看日出、云海、佛光、神灯之地。台下深崖万丈，
陡彻无底，云遮雾掩。极目四望，数百里外的大小雪山皆历历在目。因为这里
至高至洁，至险至奇，又至美至幻，常有人在这里投身云海，舍此肉身尘世。
long);
	set("outdoors", "峨嵋山");
	set("exits",([
		"east" : __DIR__"duguangtai",
	]));
	
	setup();
}

void init()
{

	add_action("do_jump", "tiao");	// 修改 命令 jump
	add_action("do_look", "look");
}

int do_look()
{
	object me = this_player();
	mixed *local;
	local = localtime(time() * 60);
	if(local[2] < 4 || local[2] >= 21)
	{
		write(BLU"初见金顶下黑黝黝一片，忽而闪现出一点、两点带蓝色的亮光，这种亮点\n"
			"越来越多，转眼便布满山谷，有的如流萤飘飞，有的如繁星闪烁。\n"NOR, me);
	}
	if(local[2] >= 4 && local[2] < 8)
	{
		write(HIR"启明星刚刚升起，一道道微白的光在东方云层闪现，一轮红日托地跳出，\n"
			"大千世界顿时在彩阳映照下呈现出无限生机。\n"NOR, me);
	}
	if(local[2] >= 8 && local[2] <= 13)
	{
		write(HIC"金顶云海，迷迷茫茫，笼罩四野，远接天际。云海轻荡时，你在金顶，脚\n"
			"踏白云，大有飘飘欲仙之感；当云涛迅猛涌来时，整个金顶都似在向前浮动，\n"
			"令人有乘舟欲风之意。\n"NOR, me);
	}
	if(local[2] > 13 && local[2] < 16)
	{
		write(YEL"日丽风静，云海平铺，美丽以极。阳光从你背面斜射下来，在舍身崖下形\n"
			"成彩色光环，你见到自己的身影清晰地出现在银色世界上。『光环随人动，\n"
			"人影在环中』，这就是奇妙的　※※※※※※※佛光※※※※※※※　。\n"
			"这里有一种使人献身的超人力量，令你不禁想要在此投身云海，摆脱人世\n"
			"的俗累，与天相接。\n"NOR, me);
	}
	if(local[2] >= 16 && local[2] < 21)
	{
		write(HIC"金顶云海，迷迷茫茫，笼罩四野，远接天际。云海轻荡时，你在金顶，脚\n"
			"踏白云，大有飘飘欲仙之感；当云涛迅猛涌来时，整个金顶都似在向前浮动，\n"
			"令人有乘舟欲风之意。\n"NOR, me);
	}
}

int do_jump(string arg)
{
	object me = this_player();

	mixed *local = localtime(time() * 60);
	
	if (me->is_busy() || me->is_fighting())
	{
		return notify_fail("你正忙着哪！\n");
	}
	
	if(arg != "cliff")
	{
		return notify_fail("你要往哪里跳？\n");
	}
	
	if (me->query("quest/jiuyin2/fail") >= 3 
		&& me->query("registered") < 3)
	{
		return notify_fail("你再也不敢拿生命开玩笑了。\n");
	}
	
	if ( me->query("quest/jiuyin2/fail") 
                >= (int)((me->query("combat_exp") - 1000000)/100000) 
		|| (time() - me->query("quest/jiuyin2/time")) < 86400)
	{
		return notify_fail("你犹豫了半天，想想还是算了吧。\n");
	}
	
	{
		object *ob = deep_inventory(me);
		int i = sizeof(ob);

		while (i--)
		{
			if (userp(ob[i]))
			{
				ob[i]->move(this_object());
			}
		}

		message_vision(HIR"$N纵身跳下舍身崖。\n"NOR, me);
		me->move(__DIR__"bankong");

		if(local[2] > 13 && local[2] < 15 )
		{
			if (random(me->query("kar")) > 15
				&& (int)me->query_dex(1) > 32 )
			{
				call_out("do_wait", 2, me);
			}
			else if ( me->query("hanshui_food") && random(3) == 1  )
			{
				call_out("do_wait", 2, me);
			}
			else 
			{
				call_out("do_wait1", 2, me);
			}

			return 1;
		}

		call_out("do_wait2", 2, me);
		return 1;
	}
}

void do_wait(object me)
{
	tell_object(me, HIR"你只觉得耳边呼呼风声作响，身体飞快的象下缀去....\n"NOR);
	tell_object(me, "突然你被什么东西阻挡了一下........\n");
        me->move(__DIR__"wanniansong");
	me->set("quest/jiuyin2/emeijump", 1);
	log_file("quest/jiuyin",sprintf("%-18s娥眉九阴部分失败%s次后从舍身崖成功跳下，福：%d。\n",
		me->name(1)+"("+capitalize(getuid(me))+")",
		chinese_number(me->query("quest/jiuyin2/fail")), me->query("kar")), me);
//	me->unconcious();
}

void do_wait1(object me)
{
	object *ob, *inv;
	int i, j;
	ob = all_inventory(environment(me));
	tell_object(me, HIR"你只觉得耳边呼呼风声作响，身体飞快的象下缀去....\n"NOR);
        me->move(__DIR__"shuitan");
	me->set("water", 666); 
	me->add("quest/jiuyin2/fail",1);
	me->set("quest/jiuyin2/time", time());
	log_file("quest/jiuyin",sprintf("%-18s从舍身崖往下跳失败，娥眉九阴部分失败%s次。\n",
		me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/jiuyin2/fail"))), me);
	tell_object(me, HIC"只听得扑通一声，你掉进了一个大水潭中，咕嘟咕嘟喝了好几口水....\n"NOR);
        for(i=0; i<sizeof(ob); i++) {
		inv = all_inventory(ob[i]);
		for (j = 0; j < sizeof(inv); j++)
		if (!inv[j]->query_autoload()) destruct(inv[j]);
		ob[i]->unconcious();
	}
}

void do_wait2(object me)
{
        object tmp;
        object *ob;
        int i;
	tell_object(me, HIR"你只觉得耳边呼呼风声作响，身体飞快的象下缀去....\n"NOR);
	tell_object(me, HIW"你只觉得世界正在离你远去........\n"NOR);
        me->move(__DIR__"shuitan");
        me->set_temp("last_damage_from","摔下山崖跌");
        me->add("quest/jiuyin2/fail", 1);
        me->set("quest/jiuyin2/time", time());
	log_file("quest/jiuyin",sprintf("%-18s从舍身崖往下跳失败，死，娥眉九阴部分失败%s次。\n",
		me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/jiuyin2/fail"))), me);
        me->unconcious();
        me->die();
        if (tmp = present("corpse", this_object())) {
		ob = deep_inventory(tmp);
		i = sizeof(ob);
		while (i--) if (userp(ob[i])){
			ob[i]->move(this_object());
			ob[i]->set_temp("last_damage_from","摔下山崖跌");
			ob[i]->die();
		}
		destruct(tmp);
		if (me) tell_room(this_object(), me->name()+"的尸骨都找不到了。\n");
	}
}
