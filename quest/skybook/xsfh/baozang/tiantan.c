//tangfeng@SJ 8/2004

inherit ROOM;
#include <ansi.h>
#define QUESTDIR5 "quest/雪山飞狐/宝藏/"

void create()
{
            set("short",HIW"大厅"NOR);
            set("long",@LONG
这里是宝藏图标志的天坛，巨大的广场难以想象当初如何建造。中间堆落
着一个巨大的天坛，看来是祭祀所用，可能因为年代的久远，已经有些塌陷。
但不影响其宏大的气势。
LONG
       );
        set("exits", ([
                "east" : __DIR__"midong1",
                "south" : __DIR__"midong2",
                "west" : __DIR__"midong3",
                "north" : __DIR__"midong4",
        ]));
            set("valid_startroom", 1);
            set("quest", 1);
            set("no_fight", 1);
            set("no_get", 1);
            set("baozang",1);
            setup();
}

void init()
{
int i;
  object me,ob,*obj;
  ob = this_object();
  me = this_player();
  obj = deep_inventory(me);
   i = sizeof(obj);
  while (i--)
  if (obj[i]->is_character())
      me->set_temp("out",1);
  if (me->query_temp("out")||!me->query(QUESTDIR5+"start")||!me->query_temp(QUESTDIR5+"search_ok")
        ||!me->query_temp(QUESTDIR5+"map_where")||me->query_condition("killer"))
  {
     me->delete_temp("out");
     me->delete_temp(QUESTDIR5+"search_ok");
     me->delete_temp(QUESTDIR5+"search");
          message_vision(YEL"突然$N听到一个声音道：“这里不欢迎$N！”\n"NOR,me);
    if(!wizardp(me)) 
      {
             me->move("/d/xiangyang/damen");  
           tell_object(me,YEL"你抬眼一看，这里竟然是武馆大门，刚才的一切像梦一样虚幻。\n"NOR); 
    }
    else 
     {
          if(random(2)) message_vision(YEL"$N似乎有些气愤，张口骂道：“没看出我是谁啊？我是巫师"+me->query("name")+"”\n\n"NOR,me);
          else message_vision(YEL"$N哼了一声，突然浑身散发出神才有的气势，额头隐隐约约显出几个金字："NOR+HIY+me->query("name")+NOR+YEL"！\n\n"NOR,me);
          message_vision(YEL"刚才鸟叫的声音好像也似乎因为$N的气势萎了回去。$N不由地得意地一笑。\n"NOR,me);
          message_vision(YEL"突然一个角落里飞出一只鞋子，砰的一声砸到$N头上，接着一个声音道：“管你是谁，TMD”\n"NOR ,me);
          me->unconcious();
    }
     return;   
  }
   if(ob->query("busy")&&ob->query("busy")!=me->query("id"))
  {
     tell_object(me,YEL"突然你听到一个声音道：“宝藏已经被人抢先一步了！”\n"NOR); 
     me->move("/d/xiangyang/damen");  
     me->delete_temp(QUESTDIR5+"search_ok");
      me->delete_temp(QUESTDIR5+"search");
     tell_object(me,YEL"你抬眼一看，这里竟然是武馆大门，刚才的一切像梦一样虚幻。\n"NOR); 
     return;   
   }
  ob->set("exits/up",me->query_temp(QUESTDIR5+"map_where"));
  ob->set("busy",me->query("id"));//其他玩家无法进入
  remove_call_out("check");
  call_out("check",1,me);
}
int valid_leave(object me, string dir)
{
        if ( dir == "up" && userp(me) && me->query(QUESTDIR5+"start")) this_object()->delete("busy");
        return ::valid_leave(me,dir);
}
void check(object me)
{
	object obj;
	remove_call_out("check");
	if(!me||!living(me) || !environment(me)->query("baozang"))
	{
		this_object()->delete("exits/up");
		this_object()->delete("busy");
		return;
	}
        if((obj=present("baozang tu",me))) 
        {
                            tell_object(me,YEL"你顺手丢掉"+obj->query("name")+YEL"。\n"NOR); 
              message_vision(HIC"$N丢下一张"+obj->query("name")+HIC"！\n" NOR,me);
              message_vision(obj->query("name")+HIC"落地时一闪，竟然失去了踪影！\n" NOR,me);
                    destruct(obj);
       }
  call_out("check",1,me);
}
