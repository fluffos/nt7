#include <ansi.h>
#include <weapon.h>
inherit AXE;

void finish(object me, object ob);

void create()
{
        set_name(MAG"小斧头"NOR, ({ "fu tou"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一把采药人常用的小斧头，用来砍伐（kanfa）木类药材。\n");
                set("unit", "把"); 
                set("no_get",1);
                set("no_drop",1);             
                set("no_put",1);
                set("no_give",1);   
                set("value",100000);
        }
        init_axe(20,2);
    setup();
}

void init()
{
    	if (environment()==this_player())
        	add_action("do_kanfa", "kanfa");
}

int do_kanfa()
{
  	object me = this_player();
  	object ob = this_object();
    	object weapon;

    	if( !objectp(weapon=query_temp("weapon", me) )
    	 || query("id", weapon) != "futou" )
    	if( !objectp(weapon=query_temp("secondary_weapon", me) )
    	 || query("id", weapon) != "futou" )
        	return notify_fail("你不拿着工具，找到药材也砍不下来啊！\n");

  	//if( !query("outdoors", environment(me)) )
  	//return notify_fail("你在房间里能砍到什么？砍人吗？\n");

    if( strsrch(query("short", environment(me)),"林")<0
     && strsrch(query("short", environment(me)),"木")<0
         && strsrch(query("short", environment(me)),"树")<0
              && strsrch(query("long", environment(me)),"林")<0
              && strsrch(query("long", environment(me)),"木")<0
              && strsrch(query("long", environment(me)),"树")<0 )


  	return notify_fail("只有树林里才有可能找到药用树木!\n");
  	
	if(me->is_busy())
  	return notify_fail("你现在正忙,等一下再砍吧!\n");

  	if( query("kanfa", environment(me))>time() )
  	return notify_fail("为了环境保护，请不要滥伐树木!\n");

  	me->start_busy(5);

	me->start_call_out( (: call_other, __FILE__, "finish", me, ob :), 3);
	message_vision( HIB"$N四处张望，看看能不能找到有用的树木。\n"NOR, this_player());
	return 1;
}

void finish(object me, object ob)
{
  	object mu;

  	if(random(5)>4) 
	{
  		me->start_busy(2);
  		message_vision( HIW"寻找一番之后$N一无所获，只得失望地叹了口气。\n"NOR, this_player());

   	}
  
  	else if ( random(20)<2) 
	{
  		message_vision( HIG"$N好不容易找到一棵有用的树木，砍了两下却发现斧头崩坏了!\n"NOR, this_player());
  		destruct(ob);
  	}
	else
   	{
addn("neili", -(query("neili", me)/10), 		me);
   addn("qi", -(query("qi", me)/10), 		me);
   addn("jing", -(query("jing", me)/10), 		me);
   set("kanfa", time()+20, 		environment(me));

		mu=new(__DIR__"/yao/mulei");
   		mu->move(me);
  		me->start_busy(2);

   		message_vision(HIR"$N突然发现一棵"+mu->name()+HIR"树，连忙取出斧头，费尽全身力气将其砍伐下来。\n"NOR, this_player());
	}
}
