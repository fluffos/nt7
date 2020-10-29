#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

void finish(object me, object ob);

void create()
{
        set_name(HIC"药锄"NOR, ({ "yao chu"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一把药锄，用来在地里挖掘（wajue）根类药材。\n");
                set("unit", "把"); 
                set("no_get",1);
                set("no_drop",1);             
                set("no_put",1);
                set("no_give",1);   
                set("value",100000);
        }
        init_hammer(20,2);
    setup();
}

void init()
{
    	if (environment()==this_player())
        	add_action("do_wajue", "wajue");
}

int do_wajue()
{
  	object me = this_player();
  	object ob = this_object();
    	object weapon;

    	if( !objectp(weapon=query_temp("weapon", me) )
    	 || query("id", weapon) != "yaochu" )
    	if( !objectp(weapon=query_temp("secondary_weapon", me) )
    	 || query("id", weapon) != "yaochu" )
        	return notify_fail("你手中得拿着工具才能挖药。\n");

  	if( !query("outdoors", environment(me)) )
  	return notify_fail("你在房间里挖个什么劲，要挖去外面挖！\n");

  	if(!sscanf(base_name(environment(me)),"/d/wudang/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/quanzhen/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/hengshan/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/taishan/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/huashan/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/tiezhang/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/gaochang/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/kunlun/%*s")
  	&& !sscanf(base_name(environment(me)),"/d/songshan/%*s"))
  	return notify_fail("只有名山大川，风景秀丽之处才可以挖掘药材!\n");
  	
	if(me->is_busy())
  	return notify_fail("你现在正忙,等一下再挖吧!\n");

  	if( query("wajue", environment(me))>time() )
  	return notify_fail("这里刚刚被人挖掘过，你等一会再来吧!\n");

  	me->start_busy(5);

	me->start_call_out( (: call_other, __FILE__, "finish", me, ob :), 3);
	message_vision( HIB"$N拿起药锄，在地上一阵疯狂乱刨！\n"NOR, this_player());
	return 1;
}

void finish(object me, object ob)
{
  	object gen;

  	if(random(5)>4) 
	{
  		me->start_busy(2);
  		message_vision( HIW"$N感到好象挖到什么东西了,仔细一看原来是石块!\n"NOR, this_player());

   	}
  
   else if ( random(20)<2) 
	{
  		message_vision( HIG"$N突然听到『喀嚓一声』,锄头挖断了!\n"NOR, this_player());
  		destruct(ob);
  	}
	else
   	{
addn("neili", -(query("neili", me)/10), 		me);
   addn("qi", -(query("qi", me)/10), 		me);
   addn("jing", -(query("jing", me)/10), 		me);
   set("wajue", time()+120, 		environment(me));

		gen=new(__DIR__"/yao/genlei");
   		gen->move(me);
  		me->start_busy(2);

   		message_vision(HIR"$N拿着药锄刨地三尺，挖出了一根"+gen->name()+HIR"！\n"NOR, this_player());
	}
}