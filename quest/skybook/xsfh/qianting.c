//by tangfeng@SJ 2004

inherit ROOM;
#include <ansi.h>
#define QUESTDIR2 "quest/雪山飞狐/复仇篇/"

void create()
{
	set("short",HIW "前厅" NOR);
	set("long", @LONG
这是苗家庄的前厅，由于修建年代久远，看起来已颇为陈旧，但因颇为干
净完全没有陈年旧宅的阴晦之气。
LONG);
	set("exits", ([
	  "east" : __DIR__"zhengmen",
	  "north" : __DIR__"zhenting",
]));
            set("quest",1);
	setup();
}
void init()
{
  object me,obj;
  me = this_player();
  if (me->query(QUESTDIR2+"start")
 		 &&!me->query_condition("killer")
		  &&!me->query(QUESTDIR2+"over")
		  &&!me->query_temp(QUESTDIR2+"have_kill")//增加一个标记（原来的有点乱了）
     &&me->query_temp(QUESTDIR2+"answer")
     &&!me->query_temp(QUESTDIR2+"huyidao")
     &&!me->query_temp(QUESTDIR2+"kill"))
  {
     tell_object(me,HIC"你身子还尚在空中，突然你听到“啊哟！”你咋以为自己身形被发现，不料却是苗人风发出痛苦之声，你偷眼一看，大吃一惊。”\n"
                       "地上一封破乱的书信，苗人风双手揉眼，脸现痛苦之色。在这一霎之间，你心中已然雪亮。那黑衣人眼见逃走，你夺路拦截。\n"NOR+
                    RED"“狗贼休走！”"NOR+HIC"你飞身向那黑衣人扑去，猛觉背后风声劲急，一股刚猛无比的掌力直扑自己背心，只得双掌反击，运力相卸。\n"NOR);
     message_vision(HIR"\n$N飘然落地，只见前厅里站着三个黑衣人，听到一个黑衣人喊道：并肩一起上。\n"NOR, me);
     obj=new(__DIR__"npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
     obj=new(__DIR__"npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
     obj=new(__DIR__"npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
     remove_call_out("killme");
     call_out("killme", 5, me);
    }
}
void killme(object me)
{
	object obj;
  if(!me) return;

  if (me->query(QUESTDIR2+"start")
 		 &&!me->query_condition("killer")
 		  &&!me->query_temp(QUESTDIR2+"have_kill")//增加一个标记（原来的有点乱了）
     &&me->query_temp(QUESTDIR2+"answer")
     &&!me->query_temp(QUESTDIR2+"huyidao")
     &&!me->query_temp(QUESTDIR2+"kill"))
  {
     obj=new(__DIR__"npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
     tell_object(me,HIG"\n\n哪里来的三个好手，只是行事为何如此卑鄙。不知道苗大侠伤势如何，当务之急还是尽快解决眼前敌人。\n"NOR);
     message_vision(HIC"$N听到兵刃劈风之声袭向头顶，中间夹着锁链扭动的声音，知是三节棍、链子枪一类武器，$N右手倏地伸出，抓住那$n的三节棍的棍头一抖。\n"NOR, me,obj);
     message_vision(HIC"那$n“啊”的一声，手臂酸麻，三节棍已然脱手，$N顺手挥出，拍的一响，击在$p腰眼之上。$n立时闭气，晕了过去。\n\n"NOR, me,obj);
     obj->unconcious();
  }
}
int valid_leave(object me, string dir)
{
       if (me->is_fighting())
                return notify_fail(RED"\n黑衣人大声喝道：哪里走。一把拦住你，你竟然无法离开。\n"NOR);
       if (present("heiyi ren",this_object()))
                return notify_fail(RED"\n黑衣人大声喝道：哪里走。一把拦住你，你竟然无法离开。\n"NOR);
   		if(me->query_condition("killer"))
   		          return notify_fail(RED"\n怎么进来的？？这里等wiz吧。\n"NOR);
        return ::valid_leave(me, dir);
}

