// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIC "沧海笑" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon, weapon2;
        int skill, ap, dp, damage, px, md, sx;
        int hp, hp1;
        int jy;
        int delta;

        me->clean_up_enemy();
        if( !target ) target = me->select_opponent();

        skill = me->query_skill("lonely-sword", 1);

        if( !me->is_fighting(target) )
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( skill < 200 )
                return notify_fail("你的独孤九剑等级不够，无法施展" + name() + "。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，无法施展" + name() + "。\n");

        if( me->query_skill_mapped("sword") != "lonely-sword" )
                return notify_fail("你没有激发独孤九剑，无法施展" + name() + "。\n");

        if( (int)me->query_skill("force") < 200 )
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if( !living(target) )
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        if( query("neili", me)<1000 ) 
                return notify_fail("你此时的内力不足，难以施展" + name() + "。\n"); 

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        px = target->query_skill("pixie-jian", 1);
        md = target->query_skill("moon-blade", 1);
        sx = target->query_skill("six-finger", 1);
        
        delta = ABILITY_D->check_ability(me, "ap_power-dgjj-xiao"); // 门派ab

        jy = me->query_skill("jianyi", 1);
        ap = ap + ap * jy / 1000 + me->query_skill("sword-cognize", 1); 
        
        if( px || md )
                ap += ap/5;              // 作为万剑之宗，对避邪剑法，圆月刀法有加成。

        if( sx )
                ap -= ap/5;              // 不擅长应付六脉聚气成剑远程攻击，有减成。
        
        if( delta ) ap += ap*delta/100;
        
        if( objectp(weapon2=query_temp("weapon", target)) )
        {
                msg = HIC "$N" HIC "一袭青衫，踏歌而来，口中作歌曰：\n" HBWHT "沧海一声笑，滔滔两岸潮，浮沉随浪只记今朝\n" NOR
                      HIW "歌声中，只见$N" HIW "肩膀微动，一道白光瞬间击出，射向$n。  \n"  NOR;
                
                addn("neili", -200, me);
                if( ap / 2 + random(ap) > dp )
                {
                        msg += HIR "$n" HIR "大骇，连忙举起手中兵器胡乱抵挡，却不想虎口剧痛，手中" + weapon2->name() +
                               HIR "捏不住，脱手而出。\n" NOR
                               HIC "$N" HIC "大笑道：$n" HIC "不过如此，尝尝下面这招滋味如何？\n \n" NOR;

                        weapon2->unequip();
                        weapon2->move(environment(me));
                } else
                {
                        msg += CYN "$n" HIY "心随意动，手中" + weapon2->name() +  "轻轻一点。\n" NOR
                               HIY "只听[叮]的一声响，$N" HIY "轻笑道：$n" HIY "果然了得，\n" NOR
                               HIY "可做我对手。且接这招如何？ \n \n"NOR;
                }
                message_combatd(msg, me, target);
        }
        else
        {
                msg = HIC "$N" HIC "一袭青衫，踏歌而来，口中作歌曰：\n" HBWHT "沧海一声笑，滔滔两岸潮，浮沉随浪只记今朝\n" NOR
                      HIW "$N" HIW "笑道：久闻$n" HIW "不凡，且接这招如何？  \n"  NOR;
                message_combatd(msg, me, target);

        }

        msg = HIC "$N" HIC "继续歌道：\n" HBWHT" 苍天笑，纷纷世上潮，谁负谁胜出天知晓 \n" NOR
              HIC "$N" HIC "随意挥洒手中的" + weapon->name() +"发出道道" HIW "剑气"HIC"，寒光闪闪，\n" NOR
              HIC "从四面八方朝$n" HIC" 直射而去！\n" NOR;

        damage = damage_power(me, "sword");
        damage += me->query_all_buff("damage"); 
        damage += query("jiali", me);
        damage += damage / 300 * me->query_str();
        damage = damage / 10 * 59;
        
        delta = ABILITY_D->check_ability(me, "da_power-dgjj-xiao"); // 门派ab
        if( delta ) damage += damage*delta/100;
        
        if( ap / 2 + random(ap) > dp )
        {
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 200+jy/10,
                                           HIR "$n" HIR "被漫天剑气惊得面如土色，只觉"
                                           "避无所避，挡无可挡，转眼间" HIW "剑气" HIR "临身"
                                           "全身各大穴道鲜血喷溅！\n\n" NOR);


                if( delta = ABILITY_D->check_ability(me, "fatal_blow-dgjj-xiao") ) // 门派ab
                {
                        if( random(10) < delta )
                        {
                                target->receive_damage("qi", damage*4, me);
                                target->receive_wound("qi", damage*4, me);
                                msg += HIR "紧接着，$N" HIR "追加了致命一击，给$n" HIR "造成更严重的创伤。\n" NOR;
                        }
                }

                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(3);
                addn("neili", -600, me);

        } 
        else
        {
                msg += CYN "$n" CYN "眼见漫天" HIW "剑气" CYN "，势不可挡，"
                       "身法连闪之下，堪堪避了开去，惊出一身冷汗！\n\n" NOR;
                me->start_busy(3);
                addn("neili", -500, me);
                target->start_busy(3);
        }
        message_combatd(msg, me, target);

        hp=query("qi", target);
        hp1=query("eff_qi", target);
        if( hp1 < hp ) hp = hp1;

        if( hp<query("max_qi", target)/10 )
        {
                msg  = HIR "$N" HIR "见$n" HIR"浑身浴血，已是摇摇欲坠，叹了一声道： \n" NOR
                       HIR "人生苦短，还是早早投胎去吧！手中" + weapon->name() +HIR" 一挥！\n" NOR
                       HIR "$n" HIR "喉中咯咯作响，面上尽是不甘之色，终于倒了下去。 \n\n" NOR;
                msg += HIC "$N" HIC "青衫飘飘而去，歌声如风：苍生笑，不再寂寥，豪情仍在痴痴笑笑~~ \n\n\n" NOR;
                message_combatd(msg, me, target);
                if( hp < 1 )
                        return 1;
                target->receive_damage("qi", hp*10);
                target->receive_wound("qi", hp*10);
                return 1;
        }

        msg = HIC"$N" HIC "青衫飘飘而去，歌声如风：苍生笑，不再寂寥，豪情仍在痴痴笑笑~~ \n\n\n" NOR;

        message_combatd(msg, me, target);
        return 1;
}
