//wrong
//tanfeng@SJ 8/2004

#include <ansi.h>
inherit ROOM;
#define QUESTDIR2 "quest/雪山飞狐/复仇篇/"

void create()
{
        set("short","后山");
        set("long", @LONG
古树参天，荆棘密布，一不小心就会被挂到了手脚。浓密宽厚的树叶遮蔽
了日月星辰，地上零星散落着捕蛇人踩过的脚印，四周死一般的寂静，只有风
吹过树梢的沙沙之声。遍地爬满了各种毒虫，你不禁产生了退缩之心。
LONG
        );

   set("quest",1);
        set("exits", ([
                "southeast" : __DIR__"shanlu",
        ]));
        set("outdoors", "苗疆");
        setup();
}
void init()
{
  object me = this_player();
  if(me->query(QUESTDIR2+"start"))
  {
  	call_out("greeting",3,me);
  }
}
void greeting(object me)
{
	int j;
	object obj;
	if(!me) return;
	if(!present(me,this_object())) return;
	tell_object(me,HIG"你看了看四周，发现这里根本没有人行的痕迹，或许是路走错了。\n"NOR);
	if(random(2))
	{
		      j=me->query_skill("force");
          obj=new("/d/sld/npc/dushe");
          message_vision(HIC"突然，草丛中钻出一只"+obj->name()+"。\n"NOR,me);
		      obj->set("combat_exp", me->query("combat_exp"));
		      obj->set("max_qi", me->query("max_qi")*3);
		      obj->set("eff_qi", me->query("max_qi")*3);
		      obj->set("qi", me->query("max_qi")*3);
		      obj->set("max_jing", me->query("max_jing"));
		      obj->set("jing", me->query("max_jing"));
		      obj->set("eff_jing", me->query("eff_jing"));
		      obj->set("eff_jingli", me->query("eff_jingli"));
		      obj->set("max_neili", me->query("max_neili"));
		      obj->set("jing", me->query("max_jing"));
		      obj->set("jingli", me->query("max_jingli"));
		      obj->set("neili", me->query("max_neili")*3/2);
		      obj->set("jiali", 200);
		      obj->set("str", me->query("str")*2);
		      obj->set("con", me->query("con")*2);
		      obj->set("dex", me->query("dex")*2);
		      obj->set("int", me->query("int")/2);
		      obj->set_skill("unarmed",j +random(50));
		      obj->set_skill("force",j + random(50));
		      obj->set_skill("dodge",j + random(50));
		      obj->set_skill("parry",j + random(50));
		      obj->move(environment(me));
		      obj->set_leader(me);
		      message_vision(RED"$N决定和$n一起行动。\n"NOR,obj,me);
		      obj->kill_ob(me);
	}
}
