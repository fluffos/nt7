// bainiu.c (kunlun)

#include <ansi.h>
#include <room.h>

inherit ROOM;

int do_wo(string arg);
int do_breathe();
void delete_done(object me);

void create()
{
	 set("short", "白牛山");
	 set("long",@long
这座山因终年覆盖白雪，且形状远望如一头正在吃草的牛而得名。这里寒
风呼啸，凛冽刺骨，你不禁打了个寒颤。山顶有一处平地，放有一块青色的巨
石(stone)。
long);
	 set("exits",([
             "southwest" : __DIR__"fufengshan",
         ]));

         set("item_desc", ([
	     "stone" : "这块巨石很大，可以躺下一个人。表面十分平整光滑，似乎常有人摩挲。\n",
	 ]));

         set("outdoors", "昆仑");
         setup();
}

void init()
{
	 add_action("do_wo", "wo");
	 add_action("do_breathe", "huxi");
}

int do_wo(string arg)
{
	 if ( !arg || (arg != "stone") )
		return notify_fail("你要卧在什么上面？\n");

	 if (this_player()->is_busy())
		return notify_fail("你正忙着呢。\n");

	 if (this_player()->query_temp("marks/wo"))
		return notify_fail("你已经躺在青石上了。\n");

	 this_player()->set_temp("marks/wo", 1);
	       return notify_fail("你侧身躺于青石上，意守丹田，口眼轻闭，双腿自然微曲，全身放松。\n");
}

int do_breathe()
{
	 object me=this_player();
	 string skill=me->query_skill_mapped("force");
	 string* quest_skill = ({ "jiuyin-zhengong","hamagong", "kuihua-xinfa" });
	 	 	 
 	 if( !me->query_temp("marks/wo") )
		return notify_fail("你深深吸了几口气，只觉得寒气冲进五脏六腑，体内的真气几乎提不起来。\n");

	 if (me->is_busy())
		return notify_fail("你正忙着呢。\n");

	 if( me->query_temp("marks/done") )
		return notify_fail("寒风凛冽，你刚运过功，身子正十分虚弱，先好好休息一下吧。\n");

	 if( me->query_skill("force", 1) < 51 )
		return notify_fail("你内功基底太弱，不可以随意控制内息。\n");
		
	 if(me->query_skill("force", 1) > 100)
	        return notify_fail("你的内功已经有一定基础了，在这里呼吸已经没什么作用了。\n");	

	if(!skill) skill="force";
	if( member_array(skill,quest_skill)!= -1 ) skill="force";
				
	 message_vision("$N集聚体内真气，深深吸进几口气，缓缓呼出，只觉得全身透彻清凉，心定似水，仿佛已物我浑然一体。\n", me);
	 me->receive_damage("jing", random(30));
 	 me->receive_damage("qi",   random(30));
	 me->improve_skill(skill, (int)(me->query_int())/2 + (int)(me->query_skill("force"))/5);

 	 me->set_temp("marks/done", 1);
	 call_out("delete_done", 2+random(3), me);

	 return 1;
}

void delete_done(object me)
{
	 if ( objectp(me) ) me->delete_temp("marks/done");
}

int valid_leave(object me, string dir)
{
	 me->delete_temp("marks/wo");
	 return ::valid_leave(me, dir);
}
