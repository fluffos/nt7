#include <ansi.h>
inherit ITEM;
#define QUESTDIR5 "quest/雪山飞狐/宝藏/"
string* map_where = ({"/d/hj/caoyuan1","/d/fairyland/shanxi","/d/lanzhou/qingcheng",
                      "/d/lanzhou/tumenzi","/d/lanzhou/gccheng","/d/lanzhou/wufosi",});
string* map_name = ({"草海","昆仑小溪","青城","兰州土门子","古长城","五佛寺",});

void create()
{
        set_name(HIB"宝藏图"NOR, ({ "baozang tu","tu"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "张");
                set("long","一个羊皮纸上似乎是随意记录一些山脉、河流和城镇的地图。\n"+
                           "你可以按地图上的样子对照（duizhao）你的方位。\n");
                set("value",1);
                 set("unique", 1);
                set("no_get",1);
                set("no_give",1);
                set("no_drop",1);
        }
        setup();
}

void init()
{
	if (environment()==this_player()&&!this_player()->query_condition("killer"))
	{
        add_action("do_duizhao","duizhao");
  }
}

int do_duizhao(string arg)
{
     	object me, obj,room;
     	int i;
     	string where,name;
     	me = this_player();
     	obj= this_object();
     	if(me->is_busy()) return 0;
     	if(me->is_fighting()) return 0;
     	if(!me->query(QUESTDIR5+"start")) return 0;
     	if(!present("lengyue dao",me))
     	    return notify_fail(HIY"单纯的地图无法提供足够的信息，你需要其他线索！\n"NOR);
        if( ! arg || (arg != "lengyue baodao"&& arg != "baodao"&& arg != "lengyue"))
                 return notify_fail("你对照的东西无法比较出什么结果。\n");
      if(!me->query_temp(QUESTDIR5+"yanjiu_ok"))
     		  return notify_fail(HIY"单纯的地图无法提供足够的信息，你需要其他线索！\n"NOR);
      if(!me->query_temp(QUESTDIR5+"guanzhu_ok"))
      {
           message_vision(HIC"$N将"+obj->name()+HIC"对比着冷月宝刀，翻来覆去地研究着！\n"NOR, me);
     	   me->add("neili", -150);
     	   return notify_fail(HIY"很遗憾的是，宝刀上的提示似乎还不够清晰！\n"NOR);
     	}
      if(me->query_temp(QUESTDIR5+"search_ok"))
     	   return notify_fail(HIY"地图已经什么都看不出来了！\n"NOR);
      if(me->query_temp(QUESTDIR5+"map_where"))
     	   return notify_fail(HIY"地图渐渐变得模糊，什么也看不清楚了！\n"NOR);
      i=random(sizeof(map_where));
      where=map_where[i];
      name=map_name[i];
      if(!room=find_object(where))
        room=load_object(where);
      if(!room)  return notify_fail(HIY"地图渐渐变得模糊，可能是巫师做的手脚！\n"NOR);
     	message_vision(HIC"$N将"+obj->name()+"对比着冷月宝刀，翻来覆去地研究着！\n"NOR, me);
     	tell_object(me,YEL"你发现刀身上的数条脉路，似乎和藏宝图可以对照。\n"NOR);
     	tell_object(me,YEL"你突然发现两者结合最终的标志竟然落在一个你曾经熟悉的地方——"+name+"。\n"NOR);
      me->set_temp(QUESTDIR5+"map_where",where);
      me->start_busy(1);
     	return 1;
}
