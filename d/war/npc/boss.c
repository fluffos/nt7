#include <ansi.h>
#include <combat.h>

inherit __DIR__"diablo_npc";

string *commonskill=
        ({"force","unarmed","literate","dodge","parry",});

void smart_fight();
void smart_fight1();
void setup()
{
        int i,hp,level;
	mapping coor,connect;

	level=query("skill_level")+50;

	for(i=0;i<sizeof(commonskill);i++)
	        set_skill(commonskill[i],level);
	        
	set("combat_exp",level*level*level/10);
	
	for(i=0;i<sizeof(query("element"));i++)
	        set_temp("apply/add_"+query("element")[i],level);
	 
	 set_temp("apply/reduce_"+query("element")[random(sizeof(query("element")))],100);
	 set("base_qi",level*level/5);
	 set("base_jing",level*level/5);
	 ::setup();
	
}

void create()
{
        string *names = ({HIG"怪物王"NOR}); 
        set_name( names[random(sizeof(names))], ({ "king"}));
        set("vendetta_mark","skeleton");
        set("long", "这是一只"+query("name")+"。\n");
        set("boss",1);
        set("attitude", "aggressive");
        set("element",({"earth",}));
       	set("chat_chance_combat", 50);
      	set("can_follow",1);
        set("far_distance",80);
        set("chat_msg_combat", ({
                (: smart_fight() :),
        }) );

        set("death_msg",BLU"\n$N散成了一堆肉渣。\n\n"NOR);
        // set_temp("apply/attack", 1000);
        // set_temp("apply/parry", 1000);
        //set_temp("apply/damage", 2000);
        setup();
        
  
} 

int is_undead() { return 1; }


void smart_fight()
{
	object ob;
	mapping buff;
	object target;
	string msg;
	object me = this_object();
	object *enemy;
	int i;
	
	enemy = me->query_enemy();
        
        if( !is_busy() )
	{
	        if( random(4) ) 
	        {
	                smart_fight1();
	                return;
	        }

                msg="$N"+HIY+"伸起双脚，向地面猛蹋，顿时尘土四溅。\n"NOR,this_object();
	        i = sizeof(enemy);
	        while(i--)
	        {
		        if( enemy[i] && living(enemy[i]) )
		        {
				target=enemy[i];
		                COMBAT_D->do_attack(this_object(), target) ;
			}
		}
	}	

	return;
}

void smart_fight1()
{
	object ob;
	mapping buff;
	object target;
	string msg;
	object me = this_object();
	object *enemy;
	int i,skill,damage;
	
	target = me->query_max_hate();
	if( !target || !objectp(target) )
		return;

	skill = me->query_skill("magic");
	damage = me->query_skill("magic")/5;
	
  	msg="$N"+HIM+"伸起巨臂，向$n挥舞。\n";
	addn_temp("apply/magic_attack",skill,me);
	addn_temp("apply/mag_damage",damage,me);

	target->set_temp("cant_dodge",1);
	COMBAT_D->do_attack(this_object(), target) ;
	addn_temp("apply/magic_attack",-skill,me);
	addn_temp("apply/mag_damage",-damage,me);

	delete_temp("cant_dodge",target);

	return;
}

void die()
{	
        mapping *walls;
        object ob,killer,owner,item,member,*bandit1;
	string *ks,*ks1;
	int i,next_flag;
  	mapping coor,connect;
	coor=environment()->zone_range()[query("zone")];
	ks1=keys(coor);
	
	if( member_array("connect", ks1)!=-1) 
	{
	        connect=coor["connect"];
		ks=keys(connect);
		ks-=({"num"});
	        i=sizeof(ks);}
		ob=this_object();
	        if(objectp(killer = query_temp("last_damage_from"))) {
	        	walls=query("walls",environment());
	        	if( i )
	        	if( connect["num"] )
	                {	
	                        while(i--)
	        	        {
	        	                walls[connect["num"]][ks[i]]=connect[ks[i]];
	        	                if( ks[i]=="next" ) next_flag=1; 
				}
	                        set("walls",walls,environment());
	      
	      	                if( next_flag )  
	      	                        environment()->generate_bandit(connect["next"]);
	                        tell_room(environment(),killer->query_idname()+"杀死了"+name()+",通往"+HIC+environment()->zone_range()[connect["next"]]["name"]+NOR"的通道打开了。\n",ob);
	                }
	                if( !connect ) 
	                {
	                        message_vision(HIY"恭喜,这个世界被征服了。\n"NOR,ob);
	                        CHANNEL_D->do_channel(this_object(),"chat", " [1;31m"+killer->name()+"打通了暗黑世界第"+(1+query("coor/z")/2000)+"层。 [0m");	
	                }
	      
                message_vision(HIR"\n$N一声惨嚎，倒在血泊里挣扎几下死了。\n"NOR,ob);
	        BUFF_D->debuff(ob,"all");
	       	
	       	bandit1=filter_array(children(__DIR__"bandit"),(:$1->query("zone")==$2->query("zone"):),ob);
	        if( sizeof(bandit1) ) map_array(bandit1,(:destruct($1):));
                //destruct(ob);
                ::die();
        }
}


