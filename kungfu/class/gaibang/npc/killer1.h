// Last Modified by winder on Nov. 15 2000

void init()
{
        object me, ob;
        string t_name;
        mapping fam;
        
        ::init();

        ob = this_player();
        me = this_object();
        if (ob != query("target")) return;
        t_name=query("name", ob);
        if (interactive(ob) &&
                (query_temp("songxin_ok", ob) || !ob->query_condition("gb_songxin") )
                 && !(query_temp("zuji_target", me) != t_name) )
        {
                call_out("dest",1);
        }
        if( query("no_fight", environment(ob)) && 
                !(query_temp("zuji_target", me) != t_name) && 
                query_temp("songxin_zuji", ob) )
        {
                remove_call_out("dest");
                call_out("dest2",1);
        }
        if (interactive(ob) &&
                !query("no_fight", environment(ob)) && 
                query_temp("songxin_zuji", ob) && 
                (!query_temp("songxin_zuji1", me) || !(query_temp("zuji_target", me) != t_name)) )
        {
//                me->set_temp("apply/attack",  random(30));
//                me->set_temp("apply/defense", random(30));
//                me->set_temp("apply/damage",  random(20));
                set("no_quest", 1);   
                set_temp("apply/dodge", 100+random(50), me);
                set_temp("songxin_zuji1", 1, me);
                if( !query_temp("zuji_target", me))set_temp("zuji_target", t_name, me);
                if( !query_temp("skill_set", me) )
                {
                        command("say 小子，乖乖把密函交出来吧！！！\n");
                        remove_call_out("dest");
                        call_out("dest",300);
                        remove_call_out("do_clone");
                        call_out("do_clone", 0, me, ob);
                }
                else
                {
                        command("say 想跑，还不给我交出来！！！\n");
                        me->set_leader(ob);
                        remove_call_out("dest");
                        call_out("dest",300);
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 0, ob); 
                }
        }
}
int do_clone(object me, object ob)
{
        object weapon;
    mapping killerskill1;
        
        int number,k_qi,k_neili,k_jing,i;
    string t_force,t_dodge;
    number=query("max_pot", ob);
    number = number-100;
          k_qi=query("max_qi", ob);
    k_jing=query("max_jing", ob);
         k_neili=query("max_neili", ob);

/*set killer's level*/
        if( query("combat_exp", ob)>800000 )
        {
                killerskill1 = skill2[random(sizeof(skill2))];
                number = (int)(number*(8+random(2))/10);
        } 
        if( query("combat_exp", ob)<800000 && query("combat_exp", ob)>600000 )
        {
                killerskill1 = skill2[random(sizeof(skill2))];
                number = (int)(number*(7+random(3))/10) ;
        }
        if( query("combat_exp", ob)<600000 && query("combat_exp", ob)>400000 )
        {
                killerskill1 = skill2[random(sizeof(skill2))];
                number = (int)(number*(6+random(3))/10) ;
        }
        if( query("combat_exp", ob)<400000 && query("combat_exp", ob)>200000 )
        {
                killerskill1 = skill1[random(sizeof(skill1))];
                number = (int)(number*(6+random(2))/10) ;
        }

        if( query("combat_exp", ob)<200000 )
        {
                killerskill1 = skill1[random(sizeof(skill1))];
                number = (int)(number*(5+random(3))/10) ;
        }

        if (number>200) number = 200;
     
/*set killer's skill*/
        t_force = k_force[random(sizeof(k_force))];
        t_dodge = k_dodge[random(sizeof(k_dodge))];       

        me->set_skill("force",number);
        me->set_skill("dodge",number);
        me->set_skill("parry",number);
        me->set_skill(t_force,number);
        me->set_skill(t_dodge,number);
        me->set_skill(killerskill1["t_skill"],number);
//        me->set_skill(killerskill2["t_skill"],number);
        me->set_skill(killerskill1["b_skill"],number);
//        me->set_skill(killerskill2["b_skill"],number);

/* set killer's  skill maps */

        me->map_skill("force",t_force);
        me->map_skill("dodge",t_dodge);
        me->map_skill("parry",killerskill1["t_skill"]);
        me->map_skill(killerskill1["b_skill"],killerskill1["t_skill"]);
//        me->map_skill(killerskill2["b_skill"],killerskill2["t_skill"]);

/* set killer's skill prepares */

        me->prepare_skill(killerskill1["b_skill"],killerskill1["t_skill"]);

/* copy entire dbase values */

        set("max_qi", k_qi*4/5, me);
        set("eff_qi", k_qi*4/5, me);
        set("qi", k_qi*4/5, me);
        set("max_jing", k_jing*4/5, me);
        set("eff_jing", k_jing*4/5, me);
        set("jing", k_jing*4/5, me);
        set("max_neili", k_neili*3/5, me);
        set("neili", k_neili*3/5, me);
        set("jiali", (number*3/4)-random(40), me);
        set("combat_exp",query("combat_exp",  ob), me);

        set_temp("skill_set", 1, me);
        set_temp("zuji", 1, ob);
        me->set_leader(ob);
        remove_call_out("kill_ob");
        call_out("kill_ob", 0, ob); 
//add 980624
//        call_out("checking", 1, me);                           
                return 1;
}
/*

int do_chase(object me)
{
        object dest;
        dest=find_player(query_temp("zuji_target", me));
        
        if( !objectp(dest) || !environment(dest) )        
        {
                call_out("waiting", 0, me);
                return 1;
        }
        
        me->move(environment(dest));
        me->set_leader(dest);
        command("hehe"+query("id", dest));
        
        if( !query("no_fight", environment(me)) )
        {
                call_out("do_kill", 1, me, dest);
                return 1;
        }
        else
        {
                call_out("waiting", 0, me);
                return 1;
        }
        return 1;
}

int do_kill(object me, object dest)
{

        if( objectp(dest) && present(dest, environment(me))
                  && !query("no_fight", environment(me)) )
        {
                message_vision(HIR "$N对$n说道："+RANK_D->query_rude(dest)+"，想往哪里跑！\n" NOR, me, dest);
                me->set_leader(dest);
                me->kill_ob(dest);
                dest->fight_ob(me);
                call_out("checking", 0,  me);         
        }
        else call_out("waiting", 1, me);         
        
        return 1;
}

int waiting(object me)
{
        object dest;
        dest=find_player(query("zuji_target", me));
        
        if ( objectp(dest) )
        {
                if( query_temp("songxin_ok", dest) || !dest->query_condition("gb_songxin") )
                {
                        call_out("dest", 0, me);
                        return 1;
                }
                else
                        if (dest->is_ghost())
                        {
                                delete("zuji_target", me);
                                call_out("dest3", 0, me);
                                return 1;
                        }
                        else if (me->is_fighting() && present(dest, environment(me)))
                                {
                                        call_out("checking", 0, me);
                                        return 1;
                                }
                                else if( living(me) && !query("no_fight", environment(dest)) )
                                        {
                                                call_out("do_chase", 0, me);
                                                return 1;
                                        }
        }                
        remove_call_out("waiting");
        call_out("waiting", 10, me);
    return 1;
}

int checking(object me)
{
        object ob;

        if (me->is_fighting()) 
        {
                call_out("checking", 1, me);
                return 1;
        }
        if( objectp(ob = present("corpse", environment(me)))
                 && query("victim_id", ob) == query("target_name", me) )
        {
                delete("zuji_target", me);
                call_out("dest3", 1, me);
                return 1;
        }
        
        call_out("waiting", 0, me);
        return 1;
}
*/
void dest()
{
        object me,ob;
        ob = this_player();
        me = this_object();

        write(query("name", me)+"道：这次算你命大！\n",me);
        write(query("name", me)+"匆匆离开。\n",me);

        destruct(this_object());
}

void dest2()
{
        object me,ob;
        ob = this_player();
        me = this_object();

        write(query("name", me)+"道：你躲得过初一躲不过十五，我们还会来的！\n",me);
        write(query("name", me)+"匆匆离开。\n",me);
        delete_temp("songxin_zuji", ob);

        destruct(this_object());
}
void dest3()
{
        object me;
        me = this_object();

        write(query("name", me)+"大笑道：完成任务了！\n",me);
        write(query("name", me)+"匆匆离开。\n",me);
        destruct(this_object());
}