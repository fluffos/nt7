inherit ITEM;
inherit "/d/war/diablo";
#include <ansi.h>

void create()
{

	set_name("传送门", ({"door"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
	
		set("long", "暗黑传送门。(相关指令touch,flyto)\n");
		set("unit", "个");
		set("base_weight", 50);
		set("door",1);
		set("no_get",1);
		set("zone","roger");
			
	
		set("act","act1");

	}
	set_coor();

}

	
	

void init()
{
	add_action("do_touch","touch");
	add_action("do_flyto","flyto");
}

int do_touch(string arg)
{
	object me,obj;
	int i,j;
	mapping trans,coor;
	string *ks,msg;
	me=this_player();
	
	trans=query("trans_"+query("act"),me);
	if( mapp(trans)) ks=keys(trans);
        if( !arg||!objectp(obj=present(arg,environment(me))) )
	        return 0;
        if( obj!=this_object() )  return 0;
        if( !wizardp(me)&&me->distance(obj)>40 ) 
	{
	        tell_object(me,"请再靠近一点，40米以内。\n");
	        return 1;
	}
	
	coor=([ "coor_x":query("coor/x"),
	        "coor_y":query("coor/y"),
	        "coor_z":query("coor/z"),
	        ]);
						
	
	tell_object(me,HIG"你开启了小站传送门的灯光。\n"NOR);
	//if(!trans||member_array(query("zone"),ks)==-1)
	{	
	        if( !trans) trans=([]);
	        trans+=([query("zone"):coor]);
                set("trans_"+query("act"),trans,me);
                tell_object(me,HIG"你记录了"+query("zone")+"传送门的位置。\n"NOR);
        }
        
	msg="你能传送的地方有";
	for(j=1;j<7;j++)
	{
	        trans=query("trans_act"+j,me);
	        if( !trans ) continue;
		ks=keys(trans);
		msg+="\n第"+j+"幕:";
		for(i=0;i<sizeof(ks);i++) 
	        {		
                        msg+="|"+ks[i]+":"+environment()->zone_range()[ks[i]]["name"];
                }
        }
	tell_object(me,HIY+msg+NOR+"。(flyto)\n");
	return 1;
}

int do_flyto(string arg)
{	
        object me,obj,env;
	int i,j;
	mapping trans,coor;
	string *ks,msg;
	me=this_player();
	obj=this_object();
	
        if( me->query_busy() ) return notify_fail("你正在忙乱中。\n");
        if( me->is_fighting() ) return notify_fail("你正在战斗中。\n");
        
        msg="你能传送的地方有";
        if( !arg )  {
	        for(j=1;j<7;j++)
	        {
	                trans=query("trans_act"+j,me);
		        if( !trans ) continue;
			ks=keys(trans);	
		        msg+="\n第"+j+"幕:";
		        for(i=0;i<sizeof(ks);i++) 
	                {
                                msg+="|"+ks[i]+":"+environment()->zone_range()[ks[i]]["name"];
                        }
                }
	        tell_object(me,HIY+msg+NOR+"。(flyto)\n");
	        return 1;
	}
        if( !wizardp(me)&&me->distance(obj)>40 ) return notify_fail("请再靠近一点，40米以内。\n");
	
	env = environment();
	for(j=1;j<7;j++)
	{
	        trans=query("trans_act"+j,me);
	        if( !mapp(trans) ) continue;//return notify_fail("你还没有开启这个区域的传送门。\n");
		ks=keys(trans);
		for(i=0;i<sizeof(ks);i++) 
	        {
	                if(member_array(arg,ks)==-1) continue;//return notify_fail("你还没有开启这个区域的传送门。\n");
		 	
		        delete_temp("moving_target",me);
	                delete_temp("moving",me);
	                set("coor/x",trans[arg]["coor_x"],me);
                        set("coor/y",trans[arg]["coor_y"],me);
                        set("coor/z",trans[arg]["coor_z"],me);
                        
 	                tell_object(me,HIG"眨眼间你被传送到了"+HIY+arg+NOR+"。\n");
 	                
 			if( arg=="rogoin"&&!query("generate/kennel",env) )
 		                env->generate_bandit("kennel");
 			if( arg=="dock"&&!query("generate/forest",env) )
 		                env->generate_bandit("forest");
 			if( arg=="bastion"&&!query("generate/godtown",env))
 		                env->generate_bandit("godtown");
 			if( arg=="harlow"&&!query("generate/iceplate",env))
 		                env->generate_bandit("iceplate");
 			if( arg=="terob"&&!query("generate/roba",env))
 		                env->generate_bandit("roba");
 	                if( !query("generate/"+arg,env)&&arg!="roger")
 		        {
                                env->generate_bandit(arg);
 	                }
 	
 	
 	                me->start_busy(2);
 	                return 1;
	
                }
        }
        return notify_fail("你还没有开启这个区域的传送门。\n");
}



