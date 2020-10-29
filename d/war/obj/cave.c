#include <ansi.h>
inherit ITEM;
inherit "/d/war/diablo";

#define L_SIZE 600
#define S_SIZE 100
void create()
{

	set_name("废弃的洞穴", ({"cave"}));
	/*if( clonep() )
		set_default_object(__FILE__);
	else*/ {
	
		set("long", "废弃的洞穴。(相关指令touch)\n");
		set("unit", "个");
		set("base_weight", 50);
		
		set("no_get",1);
		set("zone","roger");
		set("enter_num",1);
		set("level",200);
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
	object me,obj,exit;
	int i,n;
	mapping trans,coor,*walls;
	string *ks,msg;
	
	me=this_player();
	n=100000+random(100000);

        if( !arg||!objectp(obj=present(arg,environment(me))) )
	        return 0;
	        
        if( obj!=this_object() )  
                return 0;
                
	if( query("owner_id",obj)&&query("owner_id",obj)!=me) 
	{
	        tell_object(me,"这是别人的任务洞穴，你无法进入。\n");
	        return 1;
	}
	
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
	
	if( !query("have_wall") ) 
	{
	        set("have_wall",1);
	
	        coor=	
                ([
                        "no_door":1,"no_tomb":1,"act":"act1","name":"邪恶洞穴","bandit":RED"洞穴怪"+random(100)+"型"NOR,"level":query("level"),"item":"boots",
	                "x1":query("coor/x"),"x2":query("coor/x")+L_SIZE,"y1":query("coor/y"),"y2":query("coor/y")-L_SIZE,"z1":query("coor/z")+n,"z2":query("coor/z")+n,
	        ]);
	        
	        walls=environment()->generate_wall(query("coor/x"),query("coor/y"),query("coor/z"),coor);
	        environment()->add_zone_range(([replace_string(sprintf("%O.c", obj), "\"", ""):coor]));
	        environment()->generate_bandit(replace_string(sprintf("%O.c", obj), "\"", ""),coor);

	        exit=new("/d/war/obj/out");
	        set("zone",replace_string(sprintf("%O.c", obj), "\"", ""),exit);
	        set("coor/x",query("coor/x")-80-S_SIZE+L_SIZE,exit);
	        set("coor/y",query("coor/y")+80+S_SIZE-L_SIZE,exit);
	        set("coor/z",query("coor/z")+n,exit);
	        set("out_coor",query("coor"),exit);
	
	        exit->move(environment());
                set("walls",walls,exit);
        }
	
	tell_object(me,HIG"你一头钻进了"+query("name")+"。\n"NOR);
	set("coor/x",query("coor/x")+20+S_SIZE,me);
	set("coor/y",query("coor/y")-20-S_SIZE,me);
	set("coor/z",query("coor/z")+n,me);
	
        if( query("enter_num") ) addn("enter_num",-1);
	if( !query("enter_num") )
        {
		message_vision("洞穴入口已崩塌",me);
		destruct(this_object());
        }	
	return 1;
}




