//houyuan.c

inherit ROOM;
#include <ansi.h>
#define QUESTDIR "quest/连城诀/"
#define QUESTDIR1 "quest/连城诀/雪谷激斗篇/"
#define QUESTDIR2 "quest/连城诀/武馆探密篇/"

void create()
{
        set("short", "后院");
        set("long", @LONG
这里落脚似乎是一个大院了，四周堆满了杂物，似乎很久没有人来，远远
望去是馆主冬暖阁的窗口。只是四周墙壁似乎有些奇怪。东面墙总感觉像新砌
的一样；西面墙确是下面一小半陷落，似乎可以从洞口钻过去。
LONG
    );
        setup();
}
void init()
{
	add_action("do_jump", ({"jump", "tiao"}));
	add_action("do_enter", ({"zuan"}));
	add_action("do_wa", ({"wa"}));
}
int do_jump(string arg)
{
	object room,me = this_player();
    if( arg == "chuang" || arg == "window" || arg == "chuanghu" || arg == "chuangkou")
    {
		if(me->query_skill("dodge")<100) 
		{
			message_vision(HIY"\n$N吸了一口气，想从窗口跳出去。\n"NOR,me);
			return notify_fail("万震山上前把手一伸：这位"+RANK_D->query_respect(me) +"，你要干什么？！");
		}
		if (!(room = find_object(__DIR__"woshi")))
			room = load_object(__DIR__"woshi");
		if(!room)
		{ 
			tell_object(me,HIR"\n你无论怎么跳，发现都还在原地!\n");
			log_file("quest/LCHJ", sprintf("%s(%s)缺少woshi.c文件。\n", me->name(1),me->query("id")) );	
		}
		else
		{
			message_vision(HIY"\n$N吸了一口气，乘万震山不注意，突然直接从窗口跳了进去。\n"NOR, me);
			me->move(room);
			me->start_busy(1);
			tell_room(environment(me),"\n只见一个身影飞身而过，原来是"+me->name()+"从窗户下跳了进来。\n"NOR, ({me}));                       	
		}
		return 1;
	}
	return 0;
}
int do_enter(string arg)
{
	object room,me = this_player();
    if( arg == "dong" )
    {
		if (!(room = find_object(__DIR__"citang")))
			room = load_object(__DIR__"citang");
		if(!room)
		{ 
			tell_object(me,HIR"\n你无论怎么钻，发现都还在原地!\n");
			log_file("quest/LCHJ", sprintf("%s(%s)缺少citang.c文件。\n", me->name(1),me->query("id")) );	
		}
		else
		{
			message_vision(HIY"\n$N慢慢探下身来，从洞口爬了进去。\n"NOR, me);
			me->move(room);
			me->start_busy(1);
			tell_room(environment(me),"\n只见一个人丛一个角落爬了出来，原来是"+me->name()+"。\n"NOR, ({me}));                       	
		}
		return 1;
	}
	return 0;
}
int do_wa(string arg)
{
	object me = this_player();
	if(!arg || arg!="qiang") 
		return notify_fail("你要挖什么？\n");
	if(!present("gao tou",me))
		return notify_fail("没有镐头，怎么挖墙？\n");
	if(!me->query_temp(QUESTDIR2+"askqiqiang" ))
		return notify_fail("无缘无故，你挖墙干什么？\n");
	if(!me->query_temp(QUESTDIR2+"askwan_diyun" ))
		return notify_fail("无缘无故，你挖墙干什么？\n");
	if(!me->query_temp(QUESTDIR2+"askwan_qi" ))
		return notify_fail("无缘无故，你挖墙干什么？\n");
	if(me->query_temp(QUESTDIR2+"waqiang" ))
		return notify_fail("你已经发现这里的秘密了。\n");
	if(me->is_busy())
		return notify_fail("你正累着呢。\n");
	if(me->query_temp(QUESTDIR2+"wa_qiang_ing" )<=5)
	{
        message_vision(HIC"\n$N将墙洞用力堆了几下，又抡起镐头将墙扒了一扒。\n"NOR, me);
		tell_object(me,RED"一会儿，你就累得满头大汗！\n"NOR);
		me->start_busy(3);
		me->add_temp(QUESTDIR2+"wa_qiang_ing",1);
		return 1;
	}
	message_vision(HIY"\n$N将墙洞用力堆了几下，然后抡起镐头将墙扒了开来。\n"NOR, me);
	message_vision(HBYEL"\n$N竟然发现墙壁竟然内有中空。\n"NOR, me);
	tell_object(me,CYN"\n看来，破祠堂的中年乞妇所说没错。万震山害死戚长发，嫁祸狄云。\n"NOR);
	tell_object(me,CYN"只是，连城诀的秘密究竟在什么地方呢？\n"NOR);
	me->start_busy(1);
	me->set_temp(QUESTDIR2+"waqiang",1);
	return 1;	
}

