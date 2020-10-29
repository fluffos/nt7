inherit ROOM;
#include <ansi.h>
#define QUESTDIR5 "quest/雪山飞狐/宝藏/"
#define QUESTDIR4 "quest/雪山飞狐/武功/"
void create()
{
          set("short",HIC"密室"NOR);
	  set("long",@LONG
明显这是一个密室，狭小的空间很难确定当年这里的用途。
LONG
           );

	  set("exits",([
              "out": __DIR__"shuku",
          ]));
    set("quest",1);
    set("baozang",1);
	  setup();
}
void init()
{
        add_action("do_search", "search"); 
        add_action("do_search", "xunzhao"); 
        add_action("do_search", "dig"); 
}
int valid_leave(object me, string dir)
{
      if((present("zhi tuan",me))||(present("tishi ka",me)))  return notify_fail(HIR"你携带了不允许携带出去的物品，请丢弃之后再尝试离开。\n"NOR);
       return ::valid_leave(me, dir);
}
int do_search(string arg)
{
  object me,obj;
  me = this_player();
  if (me->is_busy() || me->is_fighting())
		      return notify_fail("你正忙着哪！\n");
  message_vision(HIY"$N蹲在地上，四处寻找。\n"NOR, me);
  if(!wizardp(me)) me->start_busy(1);
  if(me->query(QUESTDIR5+"shuku")>=4||random(2)||present("zhi tuan",me))
  {
       tell_room(environment(me), me->name() + "找了半天，只弄了一手泥。\n", ({ me }));
       return notify_fail("你找了半天，什么也没找到。\n");
  }
  me->add(QUESTDIR5+"shuku",1);
  obj=new("/cmds/leitai/bwdh/obj/danwan");
  obj->set("owner",me->query("id"));
  if(me->query(QUESTDIR5+"shuku")==1) obj->set("secret_obj",1);
  obj->set("bonus","combat_exp");
  obj->move(me);
  message_vision(WHT"$N发现一颗"+obj->name()+WHT"。\n"NOR, me);
  log_file("quest/FEIHU", sprintf("%s(%s)找到密室的宝物%s。经验%d。\n"NOR, me->name(1),me->query("id"),obj->query("name"), me->query("combat_exp")) );
  me->start_busy(2);
   if(!me->query(QUESTDIR4+"lengquanshengong")&&((me->query(QUESTDIR5+"shuku")>=4 && me->query("registered")>=3)||(me->query(QUESTDIR5+"shuku")==3)))
{
	  message_vision(HIG"$N打开"+obj->name()+HIG"竟然发现里面有一张纸团。\n"NOR, me);
	  tell_object(me,HIY"你展开纸团，仔细看了看似乎是武功秘籍之类的介绍。\n"NOR);
	  destruct(obj);
	  obj=unew("/d/xingxiu/baozang/obj/zhituan");
	  if(!clonep(obj)){
		  tell_room(environment(me), me->name() + "顺手把纸团丢了。\n", ({ me }));
		  log_file("quest/FEIHU", sprintf(HIR"%s(%s)随手丢弃纸团。注意可能有BUG。\n"NOR, me->name(1),me->query("id")) );
		  return notify_fail(HIY"你看了看什么也没看懂，你顺手把纸团丢了。\n"NOR);
	  }
	  obj->set("owner",me->query("id"));
	  obj->move(me);
	  me->add_busy(1);
	  log_file("quest/FEIHU", sprintf(HIR"%s(%s)找到冷泉神功提示纸团。经验%d。\n"NOR, me->name(1),me->query("id"),me->query("combat_exp")) );
	  return 1;
  }
  return 1;
}
