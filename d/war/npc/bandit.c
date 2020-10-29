#include <ansi.h>

inherit __DIR__"diablo_npc";

void setup()
{
        int i,hp,level;
	mapping coor,connect;
	string num_desc;
	string *commonskill=
                ({"force","unarmed","literate","dodge","parry",});
	level=query("skill_level");
	for(i=0;i<sizeof(commonskill);i++)
	        set_skill(commonskill[i],level);
	
	set("combat_exp",level*level*level/10);
        set_temp("apply/add_"+query("element")[random(sizeof(query("element")))],level/2);
        set("base_qi",level*level/8);
        set("base_jing",level*level/8);
        
        set("int", 10);
        set("str", 100);
        set("con", 100);
        set("dex", 40);
        
        if( i=query("hero_num") ) 
        {	 	
	        set("employ/"+remove_ansi(query("name")),query("hero_num"));
	        set_name( HIC+query("name")+"群"+NOR, ({ "spirit team","team"}));
	        set("attitude", "peaceful");
	        set("vendetta_mark",0);
        }
        ::setup();
	
}

void create()
{
        string *names = ({RED"僵尸"NOR}); 
        set_name( names[random(sizeof(names))], ({ "spirit"}));
        set("vendetta_mark","skeleton");
        set("long", "这是一只"+query("name")+"。\n");
	set("can_follow",1);
        set("far_distance",50);
        set("attitude", "aggressive");
        set("chat_chance_combat", 0);
        set("chat_msg_combat", ({
                (: smart_fight() :),
        }) );
        set("skill_level", 1000);
        set("zone","blood");
        //set("hero_num",10);	
        set("death_msg",BLU"\n$N散成了一堆肉渣。\n\n"NOR);
        //set_temp("apply/attack", 1000);
        //set_temp("apply/parry", 1000);
        //set_temp("apply/damage", 2000);
 
        set("element",({"earth",}));
        setup();
        //carry_object(__DIR__"obj/bone_finger");
} 


void die()
{	
        mapping *walls;
        object ob,killer,owner,*inv,*team;
	string *ks,*ks1;
	int level,j,bonus,num;
  	mapping coor,connect,employ;
	int d_bonus;
	
	bonus=query("skill_level")*10;
	bonus=bonus*(80+25*sizeof(environment()->dusers()))/100;
        ob=this_object();
        if( objectp(killer = query_temp("last_damage_from")) ) {
                if( owner=query("possessed",killer) ) killer = owner;
					
	    	killer->add("diablo_pot",2*bonus);
	        killer->add("potential",2*bonus);
	    	tell_object(killer,HIB"你奖励了装备熟练度"+bonus+"。\n");
	        tell_object(killer,HIB"你奖励了潜能"+2*bonus+"。\n");
	        employ=query("employ",killer);
	        if( !mapp(employ) ) employ=([]);
	        if( member_array(remove_ansi(query("name")),keys(environment()->hero()))!=-1 )
	        { 
	                if(sizeof(keys(employ))<8)
	                {
	    	                if(member_array(remove_ansi(query("name")),keys(employ))==-1)	
	    	                        employ[remove_ansi(query("name"))]=1;
	    	                else employ[remove_ansi(query("name"))]+=1;
	    		        set("employ",employ,killer);
	                        tell_object(killer,HIB"你的队伍增加了1个"+remove_ansi(query("name"))+"。\n");
	                }
	                else tell_object(killer,HIB"你的队伍满了，无法增加"+remove_ansi(query("name"))+"。\n");
	        }
	        if(strsrch(query("name"),"洞穴怪")!=-1) 
	        {
	                num=sizeof(filter_array(children("/d/war/npc/bandit"),(:$1->name()==name():)));
	    	        tell_object(killer,HIB"还有"+(num-1)+"个洞穴怪。\n");
	        }
	        if(num<=1)
	        {	
	                if(!team=killer->query_team()) team=({killer});
		        d_bonus=100*(24+query("diablo/level",killer)*3)*3;
	    	        if(query("zone")==query("diablo/zone",killer)) 
	    		        GIFT_D->dungeon_reward(killer, query("quest/quest",killer),team, d_bonus);
	    	        delete("diablo/get",killer);
	    	        delete("diablo/zone",killer);
		        delete("diablo/kind",killer);
         	        killer->add("diablo/done",1);
	                if( query("diablo/npcs",killer))  destruct(query("diablo/npcs",killer));
	        }
	    				
						
                if( query("hero_num") )
           	{
           		bonus=query("hero_num")*environment()->hero()[replace_string(remove_ansi(query("name")),"群","")]["hp"]*20;
           		killer->add("potential",bonus);
           		tell_object(killer,HIB"你的队伍杀死"+this_object()->query("name")+",获得潜能"+bonus+"。\n");
                }
        }

	       
        message_vision(HIR"\n$N一声惨嚎，倒在血泊里挣扎几下死了。\n"NOR,ob);
        BUFF_D->debuff(ob,"all");
        destruct(ob);
}


