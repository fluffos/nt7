#include <ansi.h>
#include <command.h>

inherit CLASS_D("generate") + "/chinese"; 

int  is_stay_in_room(); 
void set_from_me(object me, int scale);
int get_exp_rate();
void random_move();

void create()
{
        string temp1, temp2;
        string title;
        string *ks;
        int i, sk_lvl, exp;
        int ratio, rate, nl, basic_radio;
        
        temp1 = read_file(__DIR__"fam1", 1, 1);
        temp2 = read_file(__DIR__"fam2", 1, 1);
        
        temp1 = replace_string(temp1, "\n", "");
        temp2 = replace_string(temp2, "\n", "");
        temp1 = replace_string(temp1, " ", "");
        temp2 = replace_string(temp2, " ", "");
        
        ::create(temp2); 
        set("gender", "男性" ); 
        set("age", 30 + random(30)); 
        set("attitude", "friendly"); 
        set("str",(25+random(6)));
        set("con",(25+random(6)));
        set("dex",(25+random(6)));
        set("int",(25+random(6)));
        set("chat_chance", 30); 
        set("chat_msg", ({ 
                (: random_move :),
        })); 
        set("scale", 150); 
        set("auto_perform", 1);

        setup_family(temp2);
        title=CYN+temp2+"奸邪"+NOR;
        set("title", title);
        set("title_bak", title);
        
        ratio=90+random(50);
        
        rate=get_exp_rate();
        exp=(random(rate)+1)*(random(rate)+1)*100000;  
        
        sk_lvl = to_int(pow(to_float(exp/100), 1.0 / 3)) * 10 + 1; 
        if( sk_lvl<50 ) sk_lvl = 50;

        ks = keys(this_object()->query_skills()); 
        for (i = 0; i < sizeof(ks); i++)
                this_object()->set_skill(ks[i], sk_lvl); 
        
        nl = sk_lvl*10+exp/1000;
        set("combat_exp",exp/100*ratio);
        set("max_neili",nl*ratio/100);
        set("neili",query("max_neili")*3/2);
        set("max_jingli",query("max_neili")/2);
        set("jingli",query("max_jingli"));
        set("shen_type",1);
        basic_radio=sk_lvl/10;
        set("max_qi",(query("max_neili")*ratio/200+1000*basic_radio));
        set("qi",query("max_qi"));
        set("eff_qi",query("max_qi"));
        set("max_jing",query("max_jingli")*ratio/300+400*basic_radio);
        set("eff_jing",query("max_jing"));
        set("jiali",sk_lvl);      
        
        if(exp>5000000000) title+=HIR" 世外魔头"NOR;
        else if(exp>1000000000) title+=HIG" 江湖巨枭"NOR;
        else if(exp>500000000) title+=MAG" 雄霸一方"NOR;
        else if(exp>100000000) title+=HIB" 恶贯满盈"NOR;
        else if(exp>50000000) title+=RED" 臭名昭著"NOR;
        else if(exp>10000000) title+=HIC" 江湖余孽"NOR;
        else title+=HIW" 江湖宵小"NOR;     
        set("title",title); 
        //set("env/wimpy", 60);
        
        set_temp("apply/armor", sk_lvl);
        set_temp("apply/damage", sk_lvl);
        set_temp("apply/unarmed_damage", sk_lvl);
        set_temp("apply/reduce_busy", 60);

        set_temp("chousha/fam",temp1);
        add_money("silver", 10 + random(10));

        if (clonep()) keep_heart_beat();
}

void init()
{
        object ob;
        object killer=this_object();   

        ob = this_player();
        if( !query_temp("chousha/fam", ob) || !userp(ob) /*|| 
             query_temp("chousha/fam", ob) == query_temp("chousha/fam")*/ )
                return;
        
        if( query_temp("chousha/fam", ob) == query_temp("chousha/fam") ) 
        {
                if( random(10)>8 && !ob->is_fighting() )
                {
                        command("touch "+query("id", ob));
                        command("say "+RANK_D->query_respect(ob) +"，你来得正好，我们又有强援了，哈哈！\n");
                }
        }

        //if( query("combat_exp", ob) > query("combat_exp") )
        //        set_from_me(ob, 150);
    
        if( query_temp("chousha/fam", ob) == query("family/family_name") ) 
        {
                /*
                if( query("combat_exp", killer) <= query("combat_exp", ob)*5/2
                &&  query("combat_exp", killer) >= query("combat_exp", ob)*2/5 )
                */
                if( 1 )
                {
                        message_vision(HIR"$N对$n怒喝道: “居然敢来送死，现在后悔也来不及了，认命吧！\n"NOR,killer,ob);
                
                        command("yun powerup");
                        set_temp(query("id", ob), 1, killer);
                        killer->set_leader(ob);
                        killer->kill_ob(ob); 
                        ob->kill_ob(killer);               
                } else
                if( query("combat_exp", killer)*2/5>query("combat_exp", ob) && random(5)>3 )
                        message_vision(HIC"$N对$n喝道: “杀你这种小角色怕脏了我的手，还不快给我滚！\n"NOR,killer,ob); 
                else
                if( query("combat_exp", killer)<query("combat_exp", ob)*2/5 && random(5)>3 )
                        message_vision(HIW"$N对$n大义凛然道: “撞到前辈手里我也认了，要杀要剐悉听尊便！\n"NOR,killer,ob);

                return;
        } else
        {
                add_action("do_kill","team kill");
                add_action("do_kill","kill");
                add_action("do_kill","hit");
                add_action("do_kill","fight");
                add_action("do_kill","touxi");   
                add_action("do_kill","steal");
                add_action("do_kill","beg");
                add_action("do_kill","persuade");
        }
}

void set_from_me(object me, int scale)
{
        string title;
        int exp;
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me));
        my = query_entire_dbase();

        if (my["max_qi"] > 600000)
                my["max_qi"] = 600000;

        if (my["max_jing"] < my["max_qi"] / 2)
                my["max_jing"] = my["max_qi"] / 2;
        if (my["max_jing"] > 300000)
                my["max_jing"] = 300000;

        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];

        // 这里修改
        exp = query("combat_exp", me)*12/10;
        if (exp > query("combat_exp"))
                set("combat_exp", exp);
        
        title = query("title_bak");
        if(exp>5000000000) title+=HIR"   世外魔头"NOR;
        else if(exp>1000000000) title+=HIG"   江湖巨枭"NOR;
        else if(exp>500000000) title+=MAG"   雄霸一方"NOR;
        else if(exp>100000000) title+=HIB"   恶贯满盈"NOR;
        else if(exp>50000000) title+=RED"   臭名昭著"NOR;
        else if(exp>10000000) title+=HIC"   江湖余孽"NOR;
        else title+=HIW"   江湖宵小"NOR;     
        set("env/wimpy", 60);
        set("title",title);  
        
        my["jiali"] = query_skill("force") / 2;

}

void start_escape(int time)
{
        //call_out("escape_me",time);
}

int do_kill(string arg)
{
        string what,who;
        if(!arg) return 0;
        if(this_object()->id(arg))
        {
                write("门派仇杀是非多，还是少惹为妙。\n");
                return 1;
        }
        else
        if(sscanf(arg,"%s from %s",what,who)==2 && this_object()->id(who))
        {
                write("还是到别处去施展你的本事吧。\n");
                return 1;
        }
        return 0;
}

int accept_fight(object ob)
{
        command("say 我可没兴趣陪你玩，快给我滚开。");
        return 0;
}

int accept_hit(object ob)
{
        message_vision(HIW "$N" HIW "脸色一变，闪过一道杀气。怒"
                       "喝道：好一个" + RANK_D->query_rude(ob) +
                       "，来吧！\n" NOR, this_object());

        NPC_D->copy_from_me(this_object(), ob, 150, 1);
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
        if (! living(this_object()))
                return 1;

        return accept_hit(ob);
}

int accept_ansuan(object ob)
{
        return notify_fail("那人警惕性好高，你难以下手。\n");
}

int accept_touxi(object ob)
{
        return notify_fail("那人警惕性好高，你难以下手。\n");
}


void escape_me()
{
        object ob=this_object(); 
        message_vision(
        HIB"$N大笑了几声：“今天痛痛快快地教训了这帮所谓的正道伪君子们一顿，\n"+
        "也算没有辜负掌门的重托了，哈哈哈哈！”\n说罢，一个筋斗跳出战圈，不知去向。\n"NOR,ob);
        remove_call_out("escape_me");
        destruct(ob);
}

void unconcious()
{
        die();
}

void die()
{
        int reward_exp,reward_pot,reward_score;
        object killer,me;
        int team_num,team_exp,team_pot,n;
        object *team;

        me = this_object();
        killer = me->query_last_damage_from();
        
        message_vision(HIC"$N惨嚎一声，口喷鲜血，到在地上死了。\n"NOR,me);
        
        if( killer && userp(killer) 
                && query_temp("chousha/fam", killer) == query("family/family_name", me) ) {
                reward_exp=query("combat_exp", me)/600;

                if( query("combat_exp", killer)>query("combat_exp", me)*2 )
                        reward_exp=reward_exp/2;
                if( query("combat_exp", killer)<query("combat_exp", me)/2 )
                        reward_exp=reward_exp*4/3;
                if(reward_exp > 20000) reward_exp=20000;
                if( !query_temp(query("id", killer), me) )
                {
                        tell_object(killer,HIW"可惜，你杀的人不是你该杀的！\n"NOR);
                        reward_exp=reward_exp/10;
                }
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
                                        if( query_temp("chousha/fam", team[n] )
                                        &&  query_temp("chousha/fam", team[n]) == query_temp("chousha/fam", killer )
                                        &&  team[n]->is_killing(me) )   
                                        {
                                                tell_object(team[n],HIW"你所参加的队伍奖励你奋勇杀敌之战功——"
                                                        +"你获得了"+CHINESE_D->chinese_number(team_exp)+"点实战经验和\n"
                                                        +CHINESE_D->chinese_number(team_pot)+"点潜能奖励！\n"NOR);

                                                addn("chousha_quest/reward_exp", team_exp, team[n]);
                                                addn("chousha_quest/reward_potential", team_pot, team[n]);
                                                addn("combat_exp", team_exp, team[n]);
                                                addn("potential", team_pot, team[n]);
                                                addn_temp("chousha/reward_exp", team_exp, team[n]);
                                        }
                        }
                        reward_exp=team_exp*2;
                        reward_pot=team_pot*2;
                }

                tell_object(killer,HIW"在实战中，你获得了"+
                        CHINESE_D->chinese_number(reward_exp) +"点的『实战经验』"+
                        CHINESE_D->chinese_number(reward_pot)+"点的『潜能』\n"
                        +"及"+CHINESE_D->chinese_number(reward_score)+"点综合评价奖励！\n"NOR); 
                        
                addn("chousha_quest/reward_exp", reward_exp, killer);
                addn("chousha_quest/reward_potential", reward_pot, killer);
                addn("chousha_quest/reward_score", reward_score, killer);
                addn("combat_exp", reward_exp, killer);
                addn("potential", reward_pot, killer);
                addn("score", reward_score, killer);
                addn_temp("chousha/reward_exp", reward_exp, killer);
        }

        remove_call_out("escape_me");
        return ::die();
}

int get_exp_rate()
{
        string temp;
        int exp_rate;
        int max_exp = UPDATE_D->query_max_exp();

        temp = read_file(__DIR__"exp_rate",1,1);
        exp_rate = atoi(temp);
        if( exp_rate < 6 ) exp_rate=6;
        do{
                exp_rate++;
        } while(exp_rate*exp_rate<max_exp/100000);
    
        return (exp_rate*8/5);
}

void random_move()
{
        object ob, room;
        object *obs;
        mapping exits;
        string dir;
        string *dirs;
        int i, n;
        
        ob = this_object();
        exits=query("exits", environment(ob));
        if( !exits ) return;
        dirs = keys(exits);
        n = sizeof(dirs);
        for (i = 0; i < n; i++)
        {
                if (! sizeof(dirs))
                        return;
                dir = dirs[random(sizeof(dirs))];
                if (! (room = get_object(exits[dir])))
                {
                        dirs -= ({ dir });
                        continue;
                }
                
                obs = all_inventory(room);
                obs = filter_array(obs, (: query_temp("quest_ob", $1) :));
                if (sizeof(obs) > 10) continue;  
                if (stringp(GO_CMD->query_reverse(dir)) &&
                        !query("no_fight", room) )
                        break;
                dirs -= ({ dir });
        }

        GO_CMD->main(ob, dir);
}
