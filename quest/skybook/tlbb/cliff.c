//tangfeng@SJ 2004

#include <ansi.h>
inherit ROOM;
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"

void create()
{
	set("short", HIC"峭壁"NOR);
	set("long", @LONG
这里是颂摩崖之峭壁，从这里望去，北面正是星宿一带，南面是雁门关。
站在高处，你不由感到风光无限好。
LONG
	);
 set("no_get_from", 1); 
           set("quest",1);
 set("no_sleep_room", 1);
 setup();
}

void init()
{
	object me = this_player();
  if(me->query_condition("killer")||me->query_condition("job_busy"))
  {
     message_vision(HIC"\n突然，不知道从哪里传来一个声音道：这里不欢迎$N。\n"NOR,me); 
     tell_object(me,HIR"跟着，不知道哪里来的一只神脚飞起一脚，将你一脚踢飞出去！\n"NOR);
     tell_room(environment(me),HIR"\n不知道哪里来的一只神脚飞起一脚，将"+ me->name()+ "踢飞出去！\n"NOR, ({ me }));
     if(random(2)) me->move("/d/xingxiu/silk3");
     else me->move("/d/xingxiu/jyg");
     tell_room(environment(me), HIR"\n只见"+ me->name()+ "大叫一声飞过来，摔了个狗吃屎！好帅哦~~~~~~~~\n"NOR, ({ me }));
     me->start_busy(1);
     return;
  }
	if (me->query(QUESTDIR3+"start")&&me->query_temp(QUESTDIR3+"askxiao") && !me->query_temp(QUESTDIR3+"lookcliff")&& !me->query(QUESTDIR3+"over")) {
		add_action("do_look", ({"look"}));
	}
  add_action("do_jump", ({"jump", "tiao"}));
}
int do_look(string arg)
{
	object me = this_player();

	if (me->query(QUESTDIR3+"start")&&me->query_temp(QUESTDIR3+"askxiao") && !me->query_temp(QUESTDIR3+"lookcliff")&& !me->query(QUESTDIR3+"over")) {
	 if (!arg) {
		set("long", @LONG
这里是颂摩崖之峭壁，从这里望去，北面正是星宿一带，南面是雁门关。
站在高处，你不由感到风光无限好。只是侧面一大片光滑之处非常奇怪。
LONG
);
		me->look(arg);
	 }
         else if (arg == "光滑之处"||arg == "侧面"||arg == "cliff" ||arg == "stone") {
		tell_object(me,HIR"你仔细地观察着峭壁，只见那一片山壁天生的平净光滑，但正中一大片山石上却尽是斧凿的印痕，\n"
		                  "显而易见，是有人故意将留下的字迹削去了。\n"NOR);
    tell_room(environment(me),HIC"\n"+me->name()+"凑近峭壁，似乎在寻找什么。\n"NOR, ({ me }));                       
		tell_object(me,HIC"你暗暗想道：只怕这萧峰真的是契丹人了。\n"NOR);
		me->set_temp(QUESTDIR3+"lookcliff",1);
		me->start_busy(5);
		remove_call_out("xiaofeng");
		call_out("xiaofeng",3,me);
		return 1;
	 }
	}
	else
	{
		set("long", @LONG
这里是颂摩崖之峭壁，从这里望去，北面正是星宿一带，南面是雁门关。
站在高处，你不由感到风光无限好。
LONG
);
		me->look(arg);
	}		
}
void xiaofeng(object me)
{
	object obj;
	if(!me) return;
	if(!me->query(QUESTDIR3+"start")||!me->query_temp(QUESTDIR3+"lookcliff")|| me->query(QUESTDIR3+"over"))return;
  if(present("xiao feng", environment(me)))return;
  obj=new("/d/nanyang/npc/xiaofeng");
  obj->move(environment(me));	
	return;
}
int do_jump(string arg)
{
		object room,me = this_player();

    if( arg == "down" || arg == "cliff" || arg == "峭壁")
    {
		    if(me->query_skill("dodge")<200) 
	 	    {
           message_vision(HIC"\n$N吸了一口气，尝试跳下峭壁，却突然发现风大山高，却退了回来。\n"NOR,me);
           return 1;
	      }
        message_vision(HIC"\n$N吸了一口气，一个纵身已经跳下峭壁。\n"NOR, this_player());
        if (!(room = find_object(__DIR__"silk3")))
          room = load_object(__DIR__"silk3");
        if(!room)
        { 
      	  tell_object(me,HIR"\n你无论怎么跳，发现都还在原地!\n");
      	  log_file("quest/TLBB", sprintf("%s(%s)缺少silk.c文件。\n", me->name(1),me->query("id")) );	
        }
        else
        {
        	me->move(room);
          tell_room(environment(me),HIC"\n只见一个身影飞身而下，原来是"+me->name()+"从峭壁上跳下。\n"NOR, ({ me }));                       
        }
        return 1;
    }
    return 0;
}
