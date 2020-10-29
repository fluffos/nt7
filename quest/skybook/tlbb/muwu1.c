// cool980724
// Modify By River 98/12
// COOL@SJ,9908
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "空地");
	set("long", @LONG
你定了定神，看见眼前是一块大空地，光秃秃的什么都没长，空地北面好
象有一间屋子,南面是你跳过来的树墙。
LONG
	);
	set("outdoors", "大理");

	set("exits", ([
		"north" : __DIR__"muwu2",
	]));

	setup();
}

void init()
{
	object me,obj;
	me=this_player();
	if ( interactive(me)
	 && !present("duan yanqing",this_object())
	 && me->query_temp("quest/天龙八部/凌波微步篇/kill")){
		obj=new(__DIR__"npc/dyq");
	  obj->set_name("段延庆", ({ "duan yanqing", "duan","yanqing"}) );
	  obj->set("title",HIC"四大恶人"NOR);
	  obj->set("nickname",HIG"恶贯满盈"NOR);
		obj->move(this_object());
	}
	add_action("do_jump", "jump");
	add_action("do_tiao", "tiao");
}

int do_jump(string arg)
{
	object me;
	me = this_player();
	if (!arg || arg !="wall") 
		return notify_fail("你要跳到那去？\n");
	if (random(me->query_skill("dodge",1)) < 60){ 
		write("你吸气奋力一跳，无奈运气不好，没跳过树墙，摔了下来。\n");
		write("你受了点伤!\n");
		me->add("qi", -100);
		me->add("jingli", -80);
		me->receive_wound("qi", 50);
		return 1;
	}
	else {
		write("你一吸气，轻轻巧巧的跳过了大树墙。\n");
		message("vision",me->name() + "一纵身跳过了树墙。\n",environment(me), ({me}) );
		me->start_busy(1);
		me->move(__DIR__"shanlin-6");
		message("vision",me->name() + "从树墙后面跳了过来。\n",environment(me), ({me}) );
		return 1;
	}
}

int valid_leave(object me,string dir)
{
	if( dir == "north" 
	&& objectp(present("duan yanqing", environment(me))))
		return notify_fail("段延庆挡住了路，你无法过去!\n");   
	if ( interactive(me = this_player()) 
	 && this_player()->query_temp("quest/天龙八部/凌波微步篇/kill")
	 && (dir =="north")){
		this_player()->delete_temp("quest/天龙八部/凌波微步篇/kill");
		this_player()->set_temp("quest/天龙八部/凌波微步篇/kill_duan",1);
		return 1;
	}
	return ::valid_leave(me,dir);
}
