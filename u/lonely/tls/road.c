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
		__DIR__"npc/liao-huo" : 1,
		__DIR__"npc/wuseng" : 2,
		__DIR__"npc/guest" : 1,
	]));
	setup();
  call_other("/clone/board/tianlong_b", "???");

}
void init()
{
  object me,ob,obj,room;
  me = this_player();
  ob = this_object();
  if (me->query(QUESTDIR2+"start")
     &&me->query_temp(QUESTDIR2+"jiumozhi")
     &&!me->query_temp(QUESTDIR2+"kill_dizi")
     &&!me->query(QUESTDIR2+"over")
     &&!me->query_condition("killer"))
  {
  	//如果有其他玩家在做quest，取消quest，但补偿机会
    if(ob->query("busy_id"))
    {
	    if (!(room = find_object(__DIR__"road_copy")))
			room = load_object(__DIR__"road_copy");
		if(!room)
		{
			me->delete_temp("quest/天龙八部");
			me->delete_temp("quest/busy");//任务冲突标志取消 
			//补偿玩家机会
			me->delete("quest/天龙八部/time");
			me->delete("quest/天龙八部/combat_exp");  
			tell_object(me,HIR"\n你发现似乎有些问题，你可以询问巫师。\n");
			log_file("quest/TLBB", sprintf("%s(%s)缺少road_copy.c文件。\n", me->name(1),me->query("id")) );	
			return;
		}
		if(room
			&& ((obj=present(ob->query("busy_id"),room))|| (obj=present(ob->query("busy_id"),ob))) && obj!=me)
		{
			if(present(obj,ob)) message_vision(HIR"\n$N对$n点了点头。\n",obj,me);
			else message_vision(HIR"\n远处的山路传来一阵轻啸，$N隐约听得有打斗的声音。原来是"+obj->query("family/family_name")+HIR"弟子"+obj->query("name")+HIR"。\n",me);
			tell_object(me,HIY"有"+obj->query("family/master_name")+HIY"座下高徒"+obj->query("name")+HIY"来保护天龙寺，也不犯你出手了。"NOR);
			me->delete_temp("quest/天龙八部");
			me->delete_temp("quest/busy");//任务冲突标志取消 
			log_file("quest/TLBB", sprintf("%s(%s)因为%s(%s)冲突，天龙寺失败。\n", me->name(1),me->query("id"),obj->name(1),obj->query("id")) );
			//补偿玩家机会
			me->delete("quest/天龙八部/time");
			me->delete("quest/天龙八部/combat_exp");  
			return;  
		}
	}
	ob->set("busy_id",me->query("id"));
	me->start_busy(1);
	remove_call_out("go");
	call_out("go", 1,me);   
  }      
}

void go(object me)
{
  object room,ob;
  ob = this_object();
  remove_call_out("go");
  if(!me) 
  {
  	ob->delete("busy_id");
  	return;
  }
  if(!present(me,this_object())) 
  {
	  tell_object(me,HIY"\n让你保护天龙寺，为何四处乱走？\n"NOR);
	  tell_object(me,HIY"站位错误；任务失败！！\n"NOR);
	  me->delete_temp("quest/天龙八部");
	  me->delete_temp("quest/busy");//任务冲突标志取消 
	  log_file("quest/TLBB", sprintf("%s(%s)天龙寺站位不对，失败。\n", me->name(1),me->query("id")) );
	  me->delete(QUESTDIR2+"start");
	  ob->delete("busy_id");
	  return;
  }
  if (!(room = find_object(__DIR__"road_copy")))
        room = load_object(__DIR__"road_copy");
  if(!room)
  {
	  tell_object(me,HIY"\n远处的山路传来一阵轻啸，隐约听得有打斗的声音。\n"NOR);
	  tell_object(me,HIY"但是你总是无法找到正确的地点。可以询问巫师。\n"NOR);
	  me->delete_temp("quest/天龙八部");
	  me->delete_temp("quest/busy");//任务冲突标志取消 
      ob->delete("busy_id");
	  //补偿玩家机会
 	  me->delete("quest/天龙八部/time");
	  me->delete("quest/天龙八部/combat_exp");  
  	  log_file("quest/TLBB", sprintf("%s(%s)天龙寺缺少road_copy.c文件。\n", me->name(1),me->query("id")) );
	  return;
  }
  if(room->query("busy_id"))
  {
    tell_object(me,HIY"\n远处的山路传来一阵轻啸，隐约听得有打斗的声音。\n"NOR);
	tell_object(me,HIY"你还是耐心地等待吧。\n"NOR);
    call_out("go", 5,me);   
  }
  else 
  {
  	me->move(room);
	ob->delete("busy_id");
  	log_file("quest/TLBB", sprintf("%s(%s)天龙寺防御站开始战斗。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
  }
}
int valid_leave(object me, string dir)
{
		
	if ( me->query("family/family_name") != "天龙寺" 
	 && dir != "out" 
	 && me->query("shen") < 0
	 && objectp(present("liaohuo chanshi", environment(me))))
		return notify_fail("了惑禅师拦住你，说道：天龙寺内不得随意进出。\n");

	if ( me->query("family/family_name") != "天龙寺" 
	 && dir != "out" 
	 && me->query("shen") < 0
	 && objectp(present("wu seng", environment(me))))
		return notify_fail("武僧拦住你，说道：天龙寺内不得随意进出。\n");
	return ::valid_leave(me, dir);
}
