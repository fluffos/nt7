#include <ansi.h>
inherit ITEM;
inherit "/d/war/diablo";
#include <eve.h>



void create()
{
	set_name("洞穴出口", ({"exit"}));
	/*if( clonep() )
		set_default_object(__FILE__);
	else*/ {
	
		set("long", "洞穴出口。(相关指令touch)\n");
		set("unit", "个");
		set("base_weight", 50);
		
		set("no_get",1);
		set("zone","roger");
		set("enter_num",1);
		set("no_reset",1);
		set("act","act1");
		set("cave",1);

	}
	set_coor();

}

void init()
{
	add_action("do_touch","touch");
}

int do_touch(string arg)
{
	object me,obj,*inv;
	int i;
	mapping trans,coor,*walls,*new_wall;
	string *ks,msg;
	
	me=this_player();
	walls=query("walls",environment());
	new_wall=query("walls");

        if( !arg||!objectp(obj=present(arg,environment(me))) )
	        return 0;
        
        if( obj!=this_object() )  
                return 0;
                
	if( me->query_busy() ) 	
	{
	        tell_object(me,"你正忙着呢，再等一会。\n");
	        return 1;
	}
        
        if( !wizardp(me)&&me->distance(obj)>40 ) 
	{
	        tell_object(me,"请再靠近一点，40米以内。\n");
	        return 1;
	}
	
	coor=query("out_coor");
        if( query("enter_num") ) 
                addn("enter_num",-1);

        inv=filter_array(environment()->dusers(), 
		(:environment()->query_zone($1)["bandit"]==environment()->query_zone($2)["bandit"]:),this_object());
        
        if( sizeof(filter_array(inv,(:$1->is_user():)))<2 )
        {
	        if( !query("enter_num") )
		{
		        walls=walls-new_wall;
			set("walls",walls,environment());
		        message_vision("洞穴已崩塌",me);
		        reset_eval_cost();
		        environment()->remove_zone_range(([query("zone"):environment()->query_zone(this_object())]));
		
		}					
	}
	
	tell_object(me,HIG"你一头钻出了"+query("name")+"。\n"NOR);
	set("coor",coor,me);
	
	if( !query("enter_num") ) 
	        destruct(this_object());
	        
	//me->start_busy(3);
	return 1;
}




