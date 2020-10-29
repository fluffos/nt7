#include <ansi.h>

inherit F_SSERVER;

string name() { return "千钧一击"; }

int perform(object me, object target)
{
        object weapon;
        int skill, skill1, fmsk;
        int myskill;
        int damageone;
        int damagesub;
        int damage;
        string msg;
        mixed ap,dp;
        int status_flag=0;
        int delta;

        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("千钧一击只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你未持武器，不能使用千钧一击！\n");

        if( me->query_skill("force") < 300 )
                return notify_fail("你的内功火候未到，无法施展千钧一击！\n");

        if( me->query_skill("sword") < 300 )
                return notify_fail("你的剑法火候未到，无法施展千钧一击！\n");

        if( query("max_neili", me) <= 30000 )
                return notify_fail("你的内力不够施展千钧一击！\n");
                                
        if( me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("你必须激发玄铁剑法作为剑法才能够使用千钧一击。\n");
                                
        if( me->query_skill_mapped("force") != "surge-force")
                return notify_fail("你必须激发怒海狂涛作为内功才能够使用千钧一击。\n");
                                
        if( query("neili", me) <= query("max_neili", me)/10 )
                return notify_fail("你的内力不够施展千钧一击！\n");

        if( query("jingli", me) <= 1000 )
                return notify_fail("你的精力不够施展千钧一击！\n");
                
        if( query_temp("xtj_ji_cd", me) && time()-query_temp("xtj_ji_cd", me) < 1 )
                return notify_fail("你上一个动作还没有完成，不能施用外功。\n");
                
        msg=HIW"\n$N身子左斜，左手抽出背负的"+query("name", weapon)+NOR+HIW"，顺手一招「千钧一击」!\n\n"NOR;
        
        fmsk = me->query_skill("taishang-wangqing", 1);
        ap=attack_power(me, "sword");
        dp=defense_power(target, "force");
        damage = damage_power(me, "sword");
        damage+= query("jiali", me);
        damage+= me->query_all_buff("damage");
        damage+= damage / 300 * me->query_str();
        damage+= damage * (fmsk/100)* 5 / 100;
        damage*= 2;
        addn_temp("apply/add_damage",100,me);
        delta = ABILITY_D->check_ability(me, "ap_power-xtj-ji"); // 门派ab
        if( delta ) ap += ap*delta/100;

        delta = ABILITY_D->check_ability(me, "da_power-xtj-ji"); // 门派ab
        if( delta ) damage += damage*delta/100;
        
        if (query("can_perform/surge-force/new", me) && me->query_skill("surge-force", 1) )
        {
            ap*= 2;
            damage*= 4;
            msg+= HIY"$N"HIY"一声长啸，激起一阵狂风，气浪翻翻滚滚，向两旁散开。"
            "霎时之间，便似长风动起，气云聚合，天地渺然，有如海浪滔滔！\n\n";
        }

        if ( ap/2 + random(ap) > dp )
        {
                msg+=HIC"$N力道使得极猛,挺剑送出。$n"NOR+HIC"早有提防，却万想不到来势竟是如此猛烈，眼见闪避不及，"
                "只听砰的一声猛响，登时连退了五六步，才勉强拿椿站定，登时脸如金纸。\n"NOR;
                if(random(me->query_all_buff("fatal_blow")) > 30)
                {
                    damage*= 4;
                    msg+= HIY"$N"HIY"触发致命一击，对$n"HIY"造成「400%」的伤害！\n";
                }        
                target->receive_damage("qi", damage,  me);
                target->receive_wound("qi", damage, me);
                set_temp("xtj_ji_cd",time(),me);
                addn("neili", -query("max_neili", me)/20, me);
                me->start_busy(2+random(2));
                status_flag=1;
        }

        else if( query("int", me)>random(query("int", target)*2) )
        {
                msg+=HIC"$N一剑击出，右手长袖顺势拂去，$n"NOR+HIC"顷刻间只感五脏六腑都似翻转了，站在当地，既不敢运气，\n"
                        "也不敢移动半步，便如僵了一般。\n"NOR;
                if (! target->is_busy())
                   target->start_busy(5+random(4));
                me->start_busy(2+random(2));
                status_flag=1;
        }
        else if (query("str", me)>random(query("str", target)*2) )
        {
                msg+=HIC"$N只觉对方冲撞而来的劲力绵绵不绝，越来越强,运出所有内力振臂一击。\n" NOR;
                addn("neili", -query("max_neili", me)/40, me);
                addn("neili", -query("max_neili", target)/20, target);
                me->start_busy(1+random(2));
                if (! target->is_busy())
                    target->start_busy(1+random(2));
                status_flag=1;
        }
        else
        {
                msg += HIG"$n凌空飞跃，身形疾闪，使出本门轻功，身子往回轻轻一侧，$N的发招数尽数落空。\n"NOR;
                me->start_busy(2+random(2));
        }
        addn("neili", -200, me);
        addn_temp("apply/add_damage",-100,me);
        
        if(query("neili", me) < 0) set("neili",0,me);
        if(query("neili", target) < 0) set("neili",0,target);
        
        message_combatd(sort_msg(msg)+"\n", me, target);
        if (status_flag==1) COMBAT_D->report_status(target);
        return 1;
}

