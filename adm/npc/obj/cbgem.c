#include <ansi.h>
inherit ITEM;

string *names = ({ "topaz", "ruby", "sapphire", "emerald", "diamond" });

void do_reset()
{
	delete_temp("do_busy");
}

void create()
{
        set_name(HIR "宝石合成器" NOR, ({ "hc gem" }) );
        set_weight(3000);

        set("long", HIR @LONG
这是一个可以用来快速合成升级宝石的神器，你需要将准备合成的材料放在身上就可以了。

合成宝石    hc <宝石> -<f|m> 例如：hc diamond -f，表示将要合成身上所有的diamond类宝石到flawless级别
                                   hc diamond -m，表示将要合成身上所有的diamond类宝石到magic级别

LONG NOR );
        set("value", 200000);
        set("unit", "台");
        set("no_get", 1);

        setup();
}

void init()
{
        if( !playerp(this_player()) ) return;
        
        add_action("do_cb", "hc");
}

int do_cb(string arg)
{
        object ob, me;
        object *obs1, *obs2, *obs3;
        string a, name, str1, str2, str3, str4;
        string arg1, arg2, arg3;
        int i, k, flag=0;
        
        me = this_player();
                
        if( me->is_busy() ) return notify_fail("你正忙着呢！\n"); 
        if( query_temp("do_busy") ) return notify_fail("宝石合成器气喘嘘地叹道：慢慢来 ....\n");  

        if( !arg || sscanf(arg, "%s -%s", name, a) != 2) 
        	return notify_fail("你想要合成什么？格式:hc topaz -f\n"); 
        
        if( member_array(name, names) == -1 ) 
                return notify_fail("你想要合成什么？格式:hc topaz -f\n");  
                	
        if( a != "f" && a != "m" )
        	return notify_fail("你想要合成到什么级别 -f 或 -m ？\n");  
        
        set_temp("do_busy", 1);
 	remove_call_out("do_reset");
 	call_out("do_reset", 2);  	

        str1 = "chipped "+name;
        str2 = name;
        str3 = "flawless "+name;
        str4 = "magic "+name;
        
        arg1 = name;
        arg2 = "f"+name;
        arg3 = "m"+name;
        
        obs1 = filter_array(all_inventory(me),(:query("id", $1) == $(str1) && !$1->is_item_make() :)); 
        k = sizeof(obs1)/3;
        if( k > 1000 ) k = 1000;
   	for( i=0;i<k*3;i++ ) 
        {
            	if( objectp(obs1[i]) )
                  	destruct(obs1[i]);

              	if( i < k ) {
                     	ob = new("/clone/tessera/"+arg1);
                   	ob->move(me);
                }
                flag++;
	}
		
        obs2 = filter_array(all_inventory(me),(:query("id", $1) == $(str2) && !$1->is_item_make() :));
        k = sizeof(obs2)/3;
        if( k > 1000 ) k = 1000;
	for( i=0;i<k*3;i++ ) 
        {
            	if( objectp(obs2[i]) )
                  	destruct(obs2[i]);

              	if( i < k ) {
                     	ob = new("/clone/tessera/"+arg2);
                   	ob->move(me);
                }
                flag++;
	}
	
	if( a == "m" ) {	
        	obs3 = filter_array(all_inventory(me),(:query("id", $1) == $(str3) && !$1->is_item_make() :));
        	k = sizeof(obs3)/3;
        	if( k > 1000 ) k = 1000;
		for( i=0;i<k*3;i++ ) 
        	{
            		if( objectp(obs3[i]) )
                  		destruct(obs3[i]);

              		if( i < k ) {
                     		ob = new("/clone/tessera/"+arg3);
                   		ob->move(me);
                	}
                }
                flag++;
	}
        
        if( flag < 1 ) {
                write(HIG "你没有准备足够的宝石合成所需材料。\n");
                me->start_busy(1);
                return -1;
        }
                
        write(HIR "只见宝石合成器发出一道红光从你身上扫过，你发现身上的宝石似乎发生了某些变化。\n");          
        me->start_busy(1);
        return 1;        
}

