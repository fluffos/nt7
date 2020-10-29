//tangfeng@SJ 8/2004

#include <ansi.h>
#include <room.h>
inherit ROOM;
#define QUESTDIR5 "quest/雪山飞狐/宝藏/"

void create()
{
        set("short",YEL"金库"NOR);
        set("long", @long
这里是金库，你可以看见偶尔失落的宝玉黄金，只是传说中的那无数的
宝藏，似乎并没有发现。这里明显有一些打斗的痕迹，怕是早有人来过。
long);
        set("exits", ([
                "north" : __DIR__"tiantan",
                "south" : __DIR__"midong2",
                "east" : __DIR__"midong2",
                "west" : __DIR__"midong2",
        ]));
        set("quest", 1);
        set("baozang",1);
        setup();
}
void init()
{
  object me;
  if (interactive(me = this_player()) && me->query(QUESTDIR5+"start") && me->query_temp(QUESTDIR5+"search_ok") && !me->query(QUESTDIR5+"jinku"))
  {
       remove_call_out("greeting");
       call_out("greeting", 3, me);
	   me->start_busy(3);
  }       
}
void greeting(object me)
{
	object obj;
	if(!me) return;
	if(!present(me,this_object())) return;
	if(me->query(QUESTDIR5+"jinku")) return;

	me->set(QUESTDIR5+"jinku",1);  //
	obj=new("/clone/money/gold");
	obj->set_amount(300+random(300));
	obj->move(me);
    
	message_vision(WHT"\n$N捡起一些"+obj->query("name")+WHT"！\n"NOR, me);
	obj=new("/d/xingxiu/obj/yuqi");
	obj->move(me);
	message_vision(WHT"$N捡起一块"+obj->query("name")+WHT"！\n"NOR, me);
	obj=new("/d/hj/obj/tu");
	obj->move(me);
	message_vision(WHT"$N捡起一幅"+obj->query("name")+WHT"！\n"NOR, me);
	obj=new("/d/hj/obj/tu");
	obj->move(me);
	message_vision(WHT"$N捡起一幅"+obj->query("name")+WHT"！\n"NOR, me);
	obj=new("/d/hj/obj/tu");
	obj->move(me);
	message_vision(WHT"$N捡起一幅"+obj->query("name")+WHT"！\n"NOR, me);
	obj=new("/d/hj/obj/shiqi");
	obj->move(me);
	message_vision(WHT"$N捡起一块"+obj->query("name")+WHT"！\n"NOR, me);
	obj=new("/d/hj/obj/shiqi");
	obj->move(me);
	message_vision(WHT"$N捡起一块"+obj->query("name")+WHT"！\n"NOR, me);
	obj=new("/d/hj/obj/shiqi");
	obj->move(me);
	message_vision(WHT"$N捡起一块"+obj->query("name")+WHT"！\n"NOR, me);

	tell_object(me,HIR"\n你四处转了一圈，果然找到很多玉器黄金，还有一些值钱的名迹，看来这次不虚此行啊。\n"NOR);
	tell_object(me,HIG"突然发现地上一叠不起眼的石板。你伸手捡了起来，竟然是高昌的名物！\n"NOR);
	message("channel:rumor", HIM"【谣言】传说在闯王宝藏的"+environment(me)->query("short")+HIM"里，有人找到大量宝物黄金！\n"NOR,users() );
	log_file("quest/FEIHU", sprintf("%s(%s)从宝藏中获得无数的黄金玉器和名画。经验%d。", me->name(1),me->query("id"), me->query("combat_exp")) );
}
