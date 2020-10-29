#include <ansi.h>
inherit ITEM;
void create()
{
	set_name(HIY"普通鼎炉"NOR, ({ "putong dinglu", "dinglu" }));
	set_weight(500);
	set_max_encumbrance(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "个");
		set("long", "一个小小圆圆的普通鼎炉，药房常常用它来煎药炼丹。\n");
		set("value", 1000000);
             	set("no_get",1);
            	set("no_give",1);
	}
}

int is_container() { return 1; }

void init()
{
    	if (environment()==this_player())
        	add_action("do_liandan", "liandan");
}


int do_liandan()
{  	
	object me = this_player();
	object ob = this_object();
	object *yao;
	int yaoxing, i, lv;

	if( !query("peifang", me) || !query("mubiao", me) )
        	return notify_fail("你还没拿到配方呢，炼不出来什么东西。\n");

	yao = all_inventory(ob);
	lv = sizeof(yao);
	if (lv==0)
        	return notify_fail("先把药材放到鼎炉里面再炼吧。\n");

	if (me->is_busy())
        	return notify_fail("你现在正忙着呢。\n");

	if( query_temp("fire", me) )
        	return notify_fail("先把上次的丹炼好了在干别的吧。\n");

    	for(i=0; i<lv; i++) 
	{
        	if( !query("yaoxing", yao[i]) )
        		return notify_fail("怎么什么乱七八糟的东西都往炉子里放？\n");

		yaoxing+=query("yaoxing", yao[i]);
		destruct(yao[i]);
       }

   	message_vision(MAG"$N按照胡青牛给的配方，把药材放进鼎炉，专心致志地炼制。\n"NOR, this_player());

	me->start_busy(8);
set_temp("fire", 1, 	me);
set_temp("yaoxing", yaoxing, 	me);
set_temp("lv", lv, 	me);

	call_out("fire",8, me);
	return 1;
}

void fire(object me)
{
	int fire;

	if( query("neili", me)<40000 )
	{
		message_vision (HIY"过了一会，炉中的温度似乎有些下降，$N见状连忙添了几根柴禾。\n"NOR,me);
	}
	else if( query("neili", me)<200000 )
	{
		message_vision (HIY"过了一会，炉中的温度似乎有些下降，$N见状连忙催动内力，炉中温度有所回升。\n"NOR,me);
addn("neili", -10000, 		me);
addn_temp("fire", 1, 		me);
	}
	else
	{
		message_vision (HIY"过了一会，炉中的温度似乎有些下降，$N见状连忙催动内力，鼓动"+HIR+"三味真火"+HIY+"，炉中火焰一下旺了起来。\n"NOR,me);
addn("neili", -50000, 		me);
addn_temp("fire", 2, 		me);
	}
    	me->improve_skill("liandan-shu", me->query_int()*100+random(1000));
    addn("combat_exp", 500+random(500), 	me);
    addn("potential", 100+random(200), 	me);
	tell_object(me,WHT"在炼丹中你的经验潜能有所增长，炼丹技术也有提高。\n"NOR);

	me->start_busy(5);
    	switch ( random(2) ) 
    	{

    		case 0:
     			call_out("fire",8, me);
		break;

    		case 1:
     			call_out("shoudan",8, me);
		break;

    	}

}

void shoudan(object me)
{

	object dan;

	if( query_temp("yaoxing", me) != query("peifang", me) )
	{
		dan = new(__DIR__"/dan/wumingdan");
		dan->move(me);
   		message_vision(HIW"由于配方不对，$N炼出来一个无名药品。\n"NOR, this_player());
	}

	else if( random(query_temp("fire", me))<random(query_temp("lv", me)) )
	{
		dan = new(__DIR__"/dan/wumingdan");
		dan->move(me);
   		message_vision(HIW"尽管配方正确，但是由于人品不佳，$N炼出来一个无名药品。\n"NOR, this_player());
 	}
	else
	{
		dan=new(__DIR__"/dan/"+query("mubiao", me));
		dan->move(me);
   		message_vision(HIR"历尽千辛万苦，$N终于炼出一颗珍贵的"+query("name", dan)+HIR"！\n"NOR,this_player());
   		message_vision(HIB"$N连忙把辛苦炼出的丹药收在怀里。\n"NOR, this_player());

 	}
delete_temp("yaoxing", 	me);
delete_temp("fire", 	me);
delete_temp("lv", 	me);

delete("peifang", 	me);
delete("mubiao", 	me);
}