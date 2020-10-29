//tangfeng@SJ

#include <ansi.h>
#include <room.h>

inherit ROOM;
#define QUESTDIR2 "quest/天龙八部/天龙营救篇/"

void create()
{
	set("short", HIW"白石路"NOR);
	set("long", @LONG
走进大门，只见红砖围墙，白石铺路，从这里一直通往天王殿，抬头
望去，寺中亭台楼阁规模宏大，构筑精丽，宅地连云，其气势之盛更胜于
五台，普陀等诸处佛门胜地的名山大寺。路旁立满了无量功德碑，两边各
有一小院，院中满种着松竹。
LONG);
	set("outdoors", "天龙寺");
  set("quest",1);
	set("exits", ([             
		"northup" : __DIR__"twd",
		"west" : __DIR__"yz1",
		"east" : __DIR__"yz2",
		"out" : __DIR__"gate",
	]));
	set("objects",([
		__DIR__"npc/wuseng" : 2,
		__DIR__"npc/guest" : 1,
	]));
	setup();
}
void init()
{
  object me;
  me = this_player();
  if (me->query(QUESTDIR2+"start")
     &&me->query_temp(QUESTDIR2+"jiumozhi")
     &&!me->query_temp(QUESTDIR2+"kill_dizi")
     &&!me->query(QUESTDIR2+"over")
     &&!this_object()->query("busy_id"))
  {
     me->start_busy(1);
     message_vision(HIR"\n本来就人丁稀少的天龙寺今日更显得无比萧杀。$N脸上露出担心的神色。\n",me);
     tell_object(me,HIB"你料想这场战斗定是非同小可，而这白石路，更是通往内堂的必经之路。\n"NOR); 
     this_object()->set("busy_id",me->query("id"));
     remove_call_out("killme");
     call_out("killme", 20, me);   
  }      
}
void killme(object me)
{
	object obj;
  if(!me) return;
  if(!present(me,this_object())) 
  {
    tell_object(me,HIG"你竟然不在白石路，也算你临阵逃脱，逃过一劫。只是你的江湖名望大幅下降。\n"NOR); 
    me->delete_temp("quest/天龙八部");
	me->delete_temp("quest/busy");//任务冲突标志取消 
    me->delete(QUESTDIR2+"start");
    me->add("mana",-random(300)-200);
    if(me->query("mana")<0) me->set("mana",0);
    this_object()->delete("busy_id");
	log_file("quest/TLBB", sprintf("%s(%s)没有一直呆在白石路，失败。\n", me->name(1),me->query("id")) );
  	return;
  }
  if(me->query_condition("killer"))
  {
    tell_object(me,HIG"这段时间内，你竟然不专心看守白石路，本因不再放心你了，另外你的江湖名望大幅下降。\n"NOR); 
    me->delete_temp("quest/天龙八部");
    me->delete(QUESTDIR2+"start");
	me->delete_temp("quest/busy");//任务冲突标志取消 
    me->add("mana",-random(300)-200);
    if(me->query("mana")<0) me->set("mana",0);
    this_object()->delete("busy_id");
	log_file("quest/TLBB", sprintf("%s(%s)quest期间变成tjf，失败。\n", me->name(1),me->query("id")) );
  	return;
  }
     obj=new(__DIR__"npc/dlsdizi");
     obj->set("kill_id",me->query("id"));
     obj->set("type",1);
     obj->move(environment(me)); 
     obj->set_leader(me);
     obj=new(__DIR__"npc/dlsdizi");
     obj->set("kill_id",me->query("id"));
     obj->set("type",2);
     obj->move(environment(me)); 
     obj->set_leader(me);
     obj=new(__DIR__"npc/dlsdizi");
     obj->set("kill_id",me->query("id"));
     obj->set("type",3);
     obj->move(environment(me)); 
     obj->set_leader(me);

     //玩家之间避免冲突
     remove_call_out("busy");
     call_out("busy", 1); 
	 return;
}
void busy()
{
	object ob;
	ob=this_object();
	if(!ob->query("busy_id")) return;
    if(present(ob->query("busy_id"),ob)) call_out("busy", 1);   
	else ob->delete("busy_id");
}
int valid_leave(object me, string dir)
{
	if (me->query(QUESTDIR2+"start")
     &&me->query_temp(QUESTDIR2+"jiumozhi")
     &&!me->query_temp(QUESTDIR2+"kill_dizi")
     &&!me->query(QUESTDIR2+"over"))
		return notify_fail(RED"不要乱跑，还是专心点救援天龙寺。\n"NOR);
		
  if(me->is_fighting()) return notify_fail(RED"不要乱跑，还是专心点救援天龙寺。\n"NOR);	
  
	if ( me->query("family/family_name") != "天龙寺" 
	 && dir != "out" 
	 && me->query("shen") < 0
	 && objectp(present("wu seng", environment(me))))
		return notify_fail("武僧拦住你，说道：天龙寺内不得随意进出。\n");
	return ::valid_leave(me, dir);
}
