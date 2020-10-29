#include <weapon.h>
#include <ansi.h>
inherit BLADE;

void finish(object me, object ob);

void create()
{
        set_name(RED"镰刀"NOR, ({ "lian dao"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一把采药人常用的镰刀，用来寻找（search）草类药材。\n");
                set("unit", "把"); 
                set("no_get",1);
                set("no_drop",1);             
                set("no_put",1);
                set("no_give",1);   
                set("value",100000);
        }
        init_blade(20,2);
    setup();
}

void init()
{
    	if (environment()==this_player())
        	add_action("do_search", "search");
}

int do_search()
{
  	object me = this_player();
  	object ob = this_object();
    	object weapon;

    	if( !objectp(weapon=query_temp("weapon", me) )
    	 || query("id", weapon) != "liandao" )
    	if( !objectp(weapon=query_temp("secondary_weapon", me) )
    	 || query("id", weapon) != "liandao" )
        	return notify_fail("你不拿着工具，找到药材也割不下来啊！\n");

        if( strsrch(query("short", environment(me)),"草")<0
         && strsrch(query("short", environment(me)),"丛")<0
              && strsrch(query("long", environment(me)),"草")<0
              && strsrch(query("long", environment(me)),"丛")<0 )


  	return notify_fail("只有草丛中才有可能找到药草!\n");
  	
	if(me->is_busy())
  	return notify_fail("你现在正忙,等一下再找吧!\n");

  	if( query("search", environment(me))>time() )
  	return notify_fail("为了环境保护，请不要践踏草坪!\n");

  	me->start_busy(5);

	me->start_call_out( (: call_other, __FILE__, "finish", me, ob :), 3);
	message_vision( HIB"$N四处张望，看看能不能找到有用的药草。\n"NOR, this_player());
	return 1;
}

void finish(object me, object ob)
{
  	object cao;

  	if(random(5)>3) 
	{
  		me->start_busy(2);
  		message_vision( HIW"寻找一番之后$N一无所获，只得失望地叹了口气。\n"NOR, this_player());

   	}
  
  	else if ( random(20)<1) 
	{
  		message_vision( HIG"$N好不容易找到一棵有用的药草，割了两下却发现镰刀崩坏了!\n"NOR, this_player());
  		destruct(ob);
  	}
	else
   	{
addn("neili", -(query("neili", me)/10), 		me);
   addn("qi", -(query("qi", me)/10), 		me);
   addn("jing", -(query("jing", me)/10), 		me);
   set("search", time()+20, 		environment(me));

		cao=new(__DIR__"/yao/caolei");
   		cao->move(me);
  		me->start_busy(2);

   		message_vision(HIR"$N突然发现一棵"+cao->name()+HIR"，连忙拿起镰刀，小心翼翼地将其割取下来。\n"NOR, this_player());
	}
}

