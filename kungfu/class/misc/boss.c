// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>
#include <command.h>
inherit CLASS_D("generate") + "/chinese"; 
inherit F_SSERVER;

int is_boss() { return 1; } 
int is_stay_in_room();

void create()
{
        set_name("怪物", ({ "boss" }));
        set("gender", "男性" );
        set("age", 30 + random(30));
        // set("long", "这是一个蒙面人。");
        set("attitude", "friendly");
        set("scale", 150);
        set_temp("apply/attack", 1000);
        set_temp("apply/defense", 2000);
        set_temp("apply/damage", 1000);
        set_temp("apply/unarmed_damage", 1000);
        set_temp("apply/armor", 5000);
        set_temp("apply/reduce_damage", 90);
        set_temp("apply/reduce_busy", 36);
        set_temp("apply/add_busy", 15);
        set_temp("born_time", time());

        setup();
        //if( clonep() ) keep_heart_beat();
}

int accept_fight(object ob)
{
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        kill_ob(ob);
        return -1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->start_busy(5 + random(6));
        //me->receive_wound("qi", 500 + random(600), ob);
        return HIY "$N" HIY "怒喝一声，奋力反抗，竟逼得$n" HIY "手忙脚乱。\n" NOR;
}

void heart_beat()
{
        object me, target, *enemy;
        string basic_skill, advance_skill;
        string poison_name;
        string msg;
        int ap, dp, damage;
        int i;
                
        if( is_fighting() ) {
                if( query("neili") < 1 && random(10) == 1 )
                        set("neili", query("max_neili"));
                        
                if( random(3) ) return ::heart_beat();  

                basic_skill = query("basic_skill");
                advance_skill = query("advance_skill");
                
                me = this_object();
                target = select_opponent();
                
                msg = query("stunt_msg")+"\n";
                message_combatd(msg, me, target); 

                ap = attack_power(me, basic_skill);
                damage = damage_power(me, basic_skill);
                damage *= 120;
                        
                if( query("stunt_fight_all") ) {
                        enemy = query_enemy();
                        msg = query("stunt_hit")+"\n";
                        for( i=0;i<sizeof(enemy);i++ ) {  
                                dp = defense_power(enemy[i], "parry");
                                if( ap > dp * 11 / 10 ) {
                                        enemy[i]->receive_damage("qi", damage, me); 
                                        enemy[i]->receive_wound("qi", damage / 2, me); 
                                        
                                        message("vision", msg, environment(me), ({ enemy[i] })); 
                                        COMBAT_D->report_status(enemy[i], 1); 
                                } else {
                                        tell_object(enemy[i], HIR "你见这招势不可挡，收摄心神，气凝双臂，奋力招架，堪堪招架开去，惊出一身冷汗！\n\n" NOR); 
                                }
                        }
                        return ::heart_beat();
                }
                
                if( random(2) ) dp = defense_power(target, "dodge");
                else            dp = defense_power(target, "parry");
                
                if( ap * 2 / 3 + random(ap) > dp )
                {        
                        msg = COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 500, query("stunt_hit")+"\n"); 
                        
                        message_combatd(msg, me, target); 
                        // 中毒
                        if( poison_name = query("poison_name") ) {
                                target->affect_by("poison",
                                        ([ "level"    : this_object()->query_skill("poison", 1), 
                                           "id"       : query("id", this_object()), 
                                           "name"     : poison_name,
                                           "duration" : 200 ])); 
                                tell_object(target, HIG "你中了"+this_object()->name()+"的"+poison_name+"。\n"); 
                        }
                }
                else
                {
                        msg = query("stunt_fail")+"\n";
                        message_combatd(msg, me, target); 
                }                
                
        } 
        ::heart_beat();
}

varargs void die(object killer)
{
        object *obs, *obn, env, me, ob;
        mapping tmp;
        mixed drops, rewards;
        mixed death_msg;
        string line, key;
        int value;
        
        me = this_object();

        //if( query("end_boss", me) || query("fight_boss", me) )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }

        if( !killer ) killer = me->query_last_damage_from();
        if( !killer ) killer = query_temp("last_damage_from");
        if( !killer ) return;

        if( death_msg = query("death_msg", me) ) {
                if( functionp(death_msg) )
                        evaluate(death_msg, me);
                else
                        message_vision(death_msg+"\n", me);
        }
        else
                message_vision(NOR "\n$N扑在地上挣扎了几下，腿一伸，口中喷出几口" 
                               HIR "鲜血" NOR "，死了！\n\n" NOR, me); 

        // 以下部分转移到equipmentd.c中处理,因涉及到动态物品
        if( drops = query("drops") ) {
                tmp = ([]);
                drops = explode(drops,",");
                foreach( line in drops ) {
                        if( sscanf(line,"%s:%d",key,value)!=2 ) continue;
                        else tmp[key]=value;
                }

                EQUIPMENT_D->killer_reward(killer,this_object(),tmp);
        }

        if( !(rewards = query("rewards")) ) {
                ::die(killer);
                return;
        }

        if( objectp(killer) ) {
                tmp = ([]);
                rewards = explode(rewards,",");
                foreach( line in rewards ) {
                        if( sscanf(line,"%s:%d",key,value)!=2 ) continue;
                        else tmp[key]=value;
                }

                env = environment(me);
                obs = pointerp(killer->query_team()) ?
                                killer->query_team() : ({ killer });
                obs = filter_array(obs, (: environment($1) == $(env) :));
                // 如果队长不在，则这个队成员无任何奖励
                if( killer->query_team() && (!objectp(killer->query_team_leader()) || environment(killer->query_team_leader()) != env) )
                        obs = ({ });

                if( arrayp(obn = keys(this_object()->query_hatred_list())) && sizeof(obn) > 0 )
                {
                        obn -= ({ 0 });
                        obn = filter_array(obn, (: environment($1) == $(env) :));
                        obn -= obs;
                        obs += obn;
                }
                
                foreach( object user in obs ) {
                        if( !objectp(user) ) continue;
                        /*
                        if( query("combat_exp", user) > atoi(query("limit_exp")) )
                        {
                                tell_object(user, ((killer == user)?"您":killer->name())+"杀死"+query("name")+"，但您经验与BOSS的水平相差过大，没有奖励。\n");
                                continue;
                        }
                        */

                        if( sizeof(obs) > 1 && user->is_team_leader() ) tmp["percent"] = 120;
                        else tmp["percent"] = 100;
                        GIFT_D->boss_bonus(user, tmp);
                        /*
                        CHANNEL_D->channel_broadcast("news",
                                user->query_idname()+YEL+"挑战boss战胜"+name()+YEL+"获得"+chinese_number(tmp["exp"])+"点经验奖励。\n" NOR);
                        */
                }
        }

        destruct(this_object());
        return;
}

varargs void unconcious(object defeater)
{
        object ob;

        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
        die(defeater);
        return;
}

