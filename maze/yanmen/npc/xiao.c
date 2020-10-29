inherit NPC;
#include <room.h>
#include <ansi.h>
mapping way=([ 
"/d/yanmen/road"    :     "south",
"/d/yanmen/luanshi1":     "south",
"/d/yanmen/luanshi2":     "south",
"/d/yanmen/luanshi3":     "south",
"/d/yanmen/luanshi4":     "south",
"/d/yanmen/luanshi5":     "south",
"/d/yanmen/luanshi6":     "south",
"/d/yanmen/luanshi7":     "south",
"/d/yanmen/luanshi8":     "south",
"/d/yanmen/shibi"   :     "south",
"/d/yanmen/shance"  :     "south",
"/d/yanmen/gate"    :     "south",
]);
void attack_over(object me);
void attack_begin(object me,object target,object room,object env,string dir);

int get_exp_rate();
int get_level(int exp);   

void create()
{
        int rate,lvl,ratio,basic_radio,skill,nl,exp;

        set_name("萧远山",({ "xiao yuanshan","xiao" }) );
        set("gender", "男性" );
        set("long","这就是此次领兵南侵的辽国王侯。\n");

        set("int", 30);
        set("str", 30+random(20));
        set("con", 20+random(20));
        set("dex", 20+random(20));
        set("age", 20+random(30));
        set("per", 15+random(15));                                         
        set("no_get",1);
        ratio=80+random(40);
        rate=get_exp_rate();

        exp=(rate-1)*(rate-1)*100000;
        if(exp < 1000000) exp =1000000;
        skill=get_level(exp);
        if(skill<200)    skill=200;   
        set("combat_exp",exp/100*ratio);
        nl=skill*10+exp/1000;
        set("max_neili",nl*ratio/100);
        set("neili",query("max_neili")*3/2); 
        set("max_jingli",skill*20*ratio/100);
        set("jingli",query("max_jingli"));
        basic_radio=skill/100;
        set("max_qi",(query("max_neili")*ratio/200+1000*basic_radio));
        set("qi",query("max_qi"));
        set("eff_qi",query("max_qi"));
        set("max_jing",query("max_jingli")*ratio/300+400*basic_radio);
        set("eff_jing",query("max_jing"));
        set("jiali",skill/2); 
        set("food",500);
        set("water",500);
        set_skill("longxiang", skill);
        set_skill("xue-dao", skill);
        set_skill("shenkong-xing", skill);
        set_skill("dashou-yin", skill);
        set_skill("hand",skill);
        set_skill("force",skill);
        set_skill("dodge", skill);
        set_skill("blade", skill);
        set_skill("parry", skill);
        set_skill("arrow", skill*2/3);

        map_skill("force", "longxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("parry", "xue-dao");
        map_skill("blade", "xue-dao");   

        prepare_skill("hand", "dashou-yin");   
        set_temp("zuji_quest/party","meng"); 
        set("no_cleanup",1);  
        add_temp("apply/armor",600);
        add_temp("apply/attack",200); 
        add_temp("apply/damage",200);
        setup();

        lvl=(query("str")+skill/10)/10-1;
        if( lvl > 8 ) lvl = 8;
        lvl = lvl - 2;
        if( lvl < 3 ) lvl = 3;
        carry_object("/quest/zhuzao/weapon/bow/bow"+lvl);
        carry_object("/quest/zhuzao/weapon/bow/bow"+lvl); 
        carry_object("/quest/zhuzao/weapon/bow/bow"+lvl); 
        carry_object("/quest/zhuzao/weapon/bow/bow"+lvl); 
        carry_object("/quest/zhuzao/weapon/bow/bow"+lvl); 
        carry_object(__DIR__"obj/wandao");
        carry_object(__DIR__"obj/wandao");
        carry_object(__DIR__"obj/wandao");
        carry_object(__DIR__"obj/wandao");
        carry_object(__DIR__"obj/wandao")->wield();
        carry_object(__DIR__"obj/tiejia")->wear();   
        carry_object(__DIR__"obj/pifeng")->wear();  
        carry_object(__DIR__"horse")->ride();
}

int get_level(int exp)
{
  int level=0;
  do {
      level++;
     } while(level*level*level<(exp*10));

  return level;
}

int get_exp_rate()
{
     object *ulist;
     int i,max_exp=1000000,exp_rate=6;
     ulist  =  users();
     i = sizeof(ulist);
     while (i-- )
     {
         if ( !environment(ulist[i]) ) continue;
         if ( wizardp(ulist[i]) ) continue;

         if ((int)ulist[i]->query("combat_exp") > max_exp)
         max_exp=(int)ulist[i]->query("combat_exp");
     }

     do{
         exp_rate++;
       } while(exp_rate*exp_rate<max_exp/100000);

     return (exp_rate*6/5);
}

void change_ob()
{ 
  int jungong;

  jungong=8+random( query("combat_exp")/5000000 + 1);
  if( jungong > 16 ) jungong = 16;
  set("degree_jungong", jungong);

  set("start_date",time()); 
  set("start_time",time());
  add("eff_qi",jungong*2000);
  set("qi",query("eff_qi"));
  set_temp("zuji_quest/group",jungong);
  set_temp("zuji_quest/last_move","/d/yanmen/road");
  call_out("move_me",2,this_object());
  call_out("check_me",2,this_object());
  return;
}

void move_me(object me)
{
       mapping move_way;
       string site,temp,tmp;
       object room;
       int liangcao;

       move_way=way;
       room=environment(me);
       site=file_name(room);


       if( site=="/d/yanmen/gate" )  
       {
        if( !me->query_temp("zuji_quest/attacking") )
        {
         remove_call_out("move_me");  
         message("channel:rumor",MAG"\n【宋史记载】："
         +CHINESE_D->chinese_date((time()-14*365*24*60*60))
         +MAG"，带头大哥等在雁门关未能阻挡契丹武士，导致辽国野心大增，派兵南下直逼襄阳！！\n"NOR,users()); 
         message("channel:rumor",MAG"\n【宋史记载】："
         +CHINESE_D->chinese_date((time()-14*365*24*60*60))
         +MAG"，大宋向契丹臣服，割让大片土地给契丹，大宋百姓生活在水深火热中！！\n"NOR,users()); 
        "/quest/chousha/yelao.c"->zuji_fail();
         return;
        }  
         remove_call_out("move_me"); 
         call_out("move_me",4,me); 
        return;
       }

       if( site=="/d/yanmen/shance" )
       {
        if ( room->query("defence") > 0 && !me->query_temp("zuji_quest/break") )
        {
           message("channel:rumor",MAG"\n【火线军情】大宋：一名" 
           +me->query("title")+MAG"率领的契丹突骑兵已经攻到雁门关，\n"
           +"雁门关吃紧，急待增援！！！\n"NOR,users());
        }

        if ( room->query("defence") > 0 )
        {
           me->set_temp("zuji_quest/break",1);
           command("break");
           remove_call_out("move_me");
           call_out("move_me",4,me);
           return;
        } else
        if( me->query_temp("zuji_quest/break") )
        {
           message("channel:rumor",MAG"\n【火线军情】大宋：雁门关"
           +MAG"被契丹骑兵攻破，形势危急！！！\n"NOR,users());  
           me->delete_temp("zuji_quest/break");
        } 

       }

       if( !living(me) || me->is_fighting() ||me->is_busy() 
           || me->query_temp("zuji_quest/attacking") )
       {
        remove_call_out("move_me");
        call_out("move_me",4,me);
        return;
       }                    

       if( move_way[site] )
       {
        me->set_temp("zuji_quest/last_move",site);
        me->command("go "+move_way[site]);
       } else
       if( me->query_temp("zuji_quest/last_move") )
       me->move(me->query_temp("zuji_quest/last_move"));

       message_vision(
       HIB"$N率领着一支契丹突骑兵缓缓地朝宋军大营移动着.....\n",me);
       me->start_busy(2+random(2));
       remove_call_out("move_me");
       call_out("move_me",4,me);
       return;
}

void check_me(object me)
{
       object *ob,obb,env,room,jiang;
       string *dirs,dir,temp,tmp;
       mapping exits;
       int group,i,num;

       if( !objectp(me) ) return;


       group = ( me->query("eff_qi") - me->query("max_qi") ) / 2000; 
       me->set("qi",me->query("eff_qi"));
       if( group < 1 ) group=1; 
       me->set_temp("zuji_quest/group",(group+1));     


       env=environment(me);

       if( !living(me) )
       {
        remove_call_out("check_me");
        call_out("check_me",4,me); 
        return;
       }       

       ob = all_inventory(env);
       if( sizeof(ob)>0 && !me->query_temp("zuji_quest/attack") )
       {
         for(i=0;i<sizeof(ob);i++)
         {
          obb=ob[i];
          if( !obb->is_character() ) continue;
          if(obb->query_temp("zuji_quest/party") != "qidan" )
          {
            message_vision(HIC"$N大声下令道：骑兵准备！一排排骑兵列出整齐"
            +"的方阵，\n阳光下的契丹军刀闪闪发光——突击！！"
            +"$N一声令下，\n万马齐鸣，契丹骑兵开始了可怕的冲锋！！\n"NOR,me);  

            me->set_temp("zuji_quest/attack",1);
            me->set_temp("zuji_quest/attacking",1);
            call_out("attack_over",10,me);
            attack_begin(me,obb,env,env,dir);                    
            break; 
            remove_call_out("check_me");
            call_out("check_me",1,me);
            return;
           }
          } 
        }

       if( mapp(exits = env->query("exits"))
           && !me->query_temp("zuji_quest/attack")
           && me->query("qi") > me->query_temp("zuji_quest/group")*200
           && me->query("jing") > me->query_temp("zuji_quest/group")*100 )
       {
         dirs = keys(exits);
         for(i=0; i<sizeof(dirs); i++)
         if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
         dirs[i] = 0;
         dirs -= ({ 0 });
         if( mapp(exits) ) dir=dirs[random(sizeof(dirs))];
         if (!room=find_object(exits[dir])) room=load_object(exits[dir]);

         if (room)  
         {
           ob = all_inventory(room);
           if( sizeof(ob)>0 )
           {
            for(i=0;i<sizeof(ob);i++)
            {
             if( !obb->is_character() ) continue;
             obb=ob[i];
          if(obb->query_temp("zuji_quest/party") != "qidan" )
             {
               message_vision(HIC"$N大声下令道：弓箭手准备！一排排利箭在阳"
               +"光下闪闪发光——射击！！\n$N一声令下，万弩齐发！\n"NOR,me);  
               me->set_temp("zuji_quest/attack",1);
               me->set_temp("zuji_quest/attacking",1);
               call_out("attack_over",10,me);
               attack_begin(me,obb,room,env,dir);                    
               break; 
               remove_call_out("check_me");
               call_out("check_me",1,me);
               return;
              }
             } 
           }
         }
       }

       if( !me->query_temp("zuji_quest/attack") )
       me->delete_temp("zuji_quest/attacking");

       remove_call_out("check_me");
       call_out("check_me",2,me);
       return;
}      

void attack_begin(object me,object target,object room,object env,string dir)
{
       object weapon,bow,blade,weapon2,*ilist;
       int i;

       weapon=me->query_temp("weapon");
       if(weapon) weapon->unequip();

       blade=present("wan dao",me);
       ilist=all_inventory(me);
       for(i=0;i<sizeof(ilist);i++)
       {
           if( ilist[i]->query("is_bow") )
           {
               bow = ilist[i];
               break;
           }
       }

       if( env == room ) weapon2 = blade;
       else weapon2 = bow;
       if( weapon2 )
       weapon2->wield();
       for(i=0;i<me->query_temp("zuji_quest/group");i++)
       {
          if( objectp(target) && weapon2->query("equipped") && weapon2->query("is_bow") )
              weapon2->do_shoot(target->query("id"),me,weapon2,room,dir,1);  
          else
          if( room == env && objectp(target) )
          {
           message_vision(HIC"$N指挥的契丹铁骑，万马奔腾，"
                  +"如狂风骤雨般朝$n发起了冲击！！\n"NOR,me,target);  
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0); 
          } else break;
       }
       return;
}


void attack_over(object me)
{
      if( objectp(me) )
      {
        message_vision(HIB"$N手中军刀一挥，契丹骑兵攻势一缓，重新"
        +"开始列阵，准备发起新一轮的冲击！！\n"NOR,me); 
        me->delete_temp("zuji_quest/attack");
      }
      return;
}      



void die()
{
        int reward_exp,reward_pot,reward_score;
        object killer,me;
        int team_num,team_exp,team_pot,n;
        object *team;

        me=this_object();
        killer=me->query_temp("last_damage_from");
        remove_call_out("move_me");
        remove_call_out("check_me");
         "/quest/chousha/yelao.c"->remove_enemy();
/*
        message_vision("$N率领的契丹骑兵在几经顽抗后，终于被彻底"
        +HIR"消灭了"NOR"！\n",this_object());
*/
        if(killer && (userp(killer) || killer->query("is_baby")) 
        && killer->query_temp("zuji/ask"))
        {
         reward_exp=me->query("combat_exp")/500;

         if(killer->query("combat_exp") > me->query("combat_exp")*2)
           reward_exp=reward_exp/2;
         if(killer->query("combat_exp") < me->query("combat_exp")/2)
           reward_exp=reward_exp*4/3;
         if(reward_exp < 2000) reward_exp=2000;
         if(reward_exp > 25000) reward_exp=25000;
         reward_exp=reward_exp/2+random(reward_exp/2);
         reward_pot=reward_exp/3+random(50)+50-killer->query_int()/5;
         reward_score=reward_exp/50;
         if (reward_pot<0) reward_pot=0;

        if(pointerp(team=killer->query_team()))
        {
         team_num=sizeof(team);
         team_exp=reward_exp/(team_num+1);
         team_pot=reward_pot/(team_num+1);
         for(n=0;n<team_num;n++)
         {
         if( team[n] != killer && objectp(team[n]) && environment(team[n]) )
         if( team[n]->query_temp("zuji/ask")
             && team[n]->is_killing(me) )   
          {
           tell_object(team[n],HIW"你所参加的队伍奖励你奋勇杀敌之战功——"
           +"你获得了"+CHINESE_D->chinese_number(team_exp)+"点实战经验和\n"
           +CHINESE_D->chinese_number(team_pot)+"点潜能奖励！\n"NOR);

                   team[n]->add("zuji_quest/reward_exp",team_exp);
                   team[n]->add("zuji_quest/reward_potential",team_pot);
                   team[n]->add("combat_exp",team_exp);
                   team[n]->add("potential",team_pot);
                   team[n]->add_temp("zuji/reward_exp",team_exp); 
           }
          }
          reward_exp=team_exp*2;
          reward_pot=team_pot*2;
         }

                   tell_object(killer,HIW"在实战中，你获得了"+
CHINESE_D->chinese_number(reward_exp) +"点的『实战经验』"+
CHINESE_D->chinese_number(reward_pot)+"点的『潜能』\n"
+"及"+CHINESE_D->chinese_number(reward_score)+"点综合评价奖励！\n"NOR); 
                   killer->add("zuji_quest/reward_exp",reward_exp);
                   killer->add("zuji_quest/reward_potential",reward_pot);
                   killer->add("zuji_quest/reward_score",reward_score);
                   killer->add("combat_exp",reward_exp);
                   killer->add("potential",reward_pot);
                   killer->add("score",reward_score);
                   killer->add_temp("zuji/reward_exp",reward_exp);
/*
message("channel:rumor",HIR"【故事传闻】"NOR+HIY+killer->query("name")+NOR
+HIR"杀死了"NOR+HIY+me->query("name")+NOR+HIR"，获得了"
+CHINESE_D->chinese_number(reward_exp)
+"点实战经验、"+CHINESE_D->chinese_number(reward_pot)+"点潜能\n"
+"及"+CHINESE_D->chinese_number(reward_score)+"点综合评价奖励！\n"NOR,
users());
*/
        "/quest/chousha/yelao.c"->zuji_close();
       }
        destruct(this_object());
        return;
}


