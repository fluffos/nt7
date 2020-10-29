//tangfeng@SJ 8/2004

#include <ansi.h>
#include <room.h>
inherit ROOM;
#define QUESTDIR5 "quest/雪山飞狐/宝藏/"
#define QUESTDIR4 "quest/雪山飞狐/武功/"

void create()
{
        set("short",BLU"书房"NOR);
        set("long", @long
你打量四周，看来似乎是个书房，但是架子上一本书也没有，好像连腐烂
的痕迹都没有。架子旁边是个桌子，中间早已裂开；旁边应该是几个花盆。
long);
        set("exits", ([
                "west" : __DIR__"tiantan",
                "south" : __DIR__"midong1",
                "east" : __DIR__"midong1",
                "north" : __DIR__"midong1",
        ]));
        set("quest", 1);
        set("baozang",1);
        setup();
}
void init()
{
        add_action("do_search", "xunzhao");
        add_action("do_search", "dig");
        add_action("do_search", "search");
        add_action("do_move", "move");
        add_action("do_push", "push");
        add_action("do_push", "tui");
        add_action("do_bang", "bang");
        add_action("do_move", "zhuan");
}
int do_search(string arg)
{
     object me,obj;
     me = this_player();
     if (me->is_busy() || me->is_fighting())
                   return notify_fail("你正忙着哪！\n");
      message_vision(HIY"$N蹲在地上，四处寻找。\n"NOR, me);
      if(!wizardp(me)) me->start_busy(1);
      if(me->query(QUESTDIR5+"yupei")||!me->query(QUESTDIR4+"lengquanshengong")||me->query(QUESTDIR4+"lengquanshengong_teach"))
      {
         tell_room(environment(me), me->name() + "找了半天，只弄了一手泥。\n", ({ me }));
         return notify_fail("你找了半天，什么也没找到。\n");
      }
      obj = new("/d/xingxiu/baozang/obj/yuqi");
      obj->set("owner",me->query("id"));
      obj->set("quest",1);
      obj->set("long", HIC"这是东汉玉石饰品中的一个，出自陕西，山东，河南一带。\n"
                      +"下面刻着一个“苗”字。\n"NOR);
      obj->move(me);
      message_vision(WHT"$N按照纸团提示的方位，并没有发现秘籍，但却发现一块"+obj->name()+WHT"。\n"NOR, me);
      log_file("quest/FEIHU", sprintf("%s(%s)找到苗家玉佩，解开冷泉神功。经验%d。\n", me->name(1),me->query("id"),me->query("combat_exp")) );
      me->set(QUESTDIR5+"yupei",1);
      me->start_busy(2);
      return 1;
 }

int do_push(string arg)
{
	object me,*ob;
  int i;
  me = this_player();
	if (me->is_busy() || me->is_fighting())
		      return notify_fail("你正忙着哪！\n");
	if ( !arg || (arg != "zhuo zi" &&arg != "zhuozi" &&arg != "anmen" && arg != "wall"))
       		return notify_fail("你要推动什么？\n");
  ob = deep_inventory(me);
  i = sizeof(ob);
  while (i--)
  if (ob[i]->is_character())
       		return notify_fail("你背负一人，无法推动。\n");
  if(arg=="zhuo zi"||arg=="zhuozi")
  {
    if(!me->query_temp(QUESTDIR5+"bang_zhuozi"))
       		return notify_fail("桌子太零散，无法推开。\n");
    if(me->query_temp(QUESTDIR5+"move_zhuozi"))
    {
    		message_vision(HIY"$N把桌子又推回原来的位置。\n"NOR, me);
	      me->delete_temp(QUESTDIR5+"move_zhuozi");
        me->start_busy(1);
  	    return 1;
    }
	  message_vision(HIG"$N用力将绑好的桌子全部推到角落的一边。\n"NOR, me);
	  me->set_temp(QUESTDIR5+"move_zhuozi",1);
    me->start_busy(1);
  	return 1;
  }
  if(!me->query_temp(QUESTDIR5+"move_huapen"))
       		return notify_fail("暗门的机关没有打开，无法推开。\n");
  if(!me->query_temp(QUESTDIR5+"move_zhuozi"))
       		return notify_fail("有桌子阻挡，无法推开。\n");

	message_vision(HIG"$N用力推开活动的暗门，奋力从门缝挤了进去。\n"NOR, me);
	me->move(__DIR__"mishi");
	me->delete_temp(QUESTDIR5+"move_zhuozi");
	me->delete_temp(QUESTDIR5+"move_huapen");
	me->delete_temp(QUESTDIR5+"bang_zhuozi");
  me->start_busy(1);
	tell_room(environment(me), me->name() + "从外面挤了进来。\n", ({ me }));
	return 1;
}
int do_move(string arg)
{
	object me;
  me = this_player();
	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着哪！\n");
	if ( !arg || (arg != "huapen" && arg != "hua pen"))
       		return notify_fail("你要转动什么？\n");
  if(me->query_temp(QUESTDIR5+"move_huapen"))
  {
  	message_vision(HIG"$N把地上的花盆转回原位。\n"NOR, me);
	  me->delete_temp(QUESTDIR5+"move_huapen");
    me->start_busy(1);
    return 1;
  }
	message_vision(HIG"$N转了转地上的花盆。\n"NOR, me);
	me->set_temp(QUESTDIR5+"move_huapen",1);
  me->start_busy(1);
	tell_room(me,"你突然发现桌子后边似乎有道暗门。\n");
	return 1;
}
int do_bang(string arg)
{
	object me,ob;
  me = this_player();
	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着哪！\n");
	if ( !arg || (arg != "zhuo zi" && arg != "zhuozi"))
       		return notify_fail("你要绑什么？\n");
  if(me->query_temp(QUESTDIR5+"bang_zhuozi"))
       		return notify_fail("你已经绑好了。\n");
  if(!(ob=present("sheng zi",me))) 
       		return notify_fail("你没有绳子，拿什么绑？\n");
       		
	message_vision(HIG"$N将快要零散的桌子，用绳子绑在一起。\n"NOR, me);
	me->set_temp(QUESTDIR5+"bang_zhuozi",1);
  me->start_busy(1);
	return 1;
}
