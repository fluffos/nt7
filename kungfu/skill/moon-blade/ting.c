
#include <ansi.h>
#include <combat.h>

string name() { return HIM "小楼一夜听春雨" NOR; }

#include "/kungfu/skill/eff_msg.h"
inherit F_SSERVER;

int perform(object me, object target)
{
        mapping buff;
        object weapon;
        object *obs;
        int damage;
        string msg;
        int ap, dp, md, ly;
        int flag, i, p;
        int fmsk = me->query_skill("motun-tianxia", 1);
        int delta, delta2;
        int time;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 160)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("moon-blade", 1) < 200)
                return notify_fail("你的圆月弯刀还不到家，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "moon-blade")
                return notify_fail("你没有激发圆月弯刀，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HBRED "小楼一夜听春雨：圆月落，刀光起。纵横大地十万里。刀光寒如雪，何处听春雨？\n" NOR
              HIY "只听唰的一声，" + weapon->name() + HIY "出手了！一切只能以一个快字去形容，发生在肉眼难看清楚的高速下，\n"
              "$N" HIY "这一刀劈出时，好像也是直直的，但是这笔直劈出来的一刀，竟忽然闪起了一道弯弯的刀光。\n"
              "弯弯的刀，弯弯的刀光，开始时宛如一弯新月，忽然间就变成了一道飞虹。这一道弯弯的刀光闪起时，\n"
              + weapon->name() + HIY "上的妖异之气，使人为之震眩迷惑。\n" NOR;

        ap = attack_power(me, "blade");
        ap += ap * (fmsk/100)* 5 / 100;
        dp = defense_power(target, "dodge");

        md = me->query_skill("moon-blade", 1);
        ly = target->query_skill("lonely-sword", 1);
        
        delta = ABILITY_D->check_ability(me, "ap_power-yywd-ting"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        if (ap * 2 / 3 + random(ap) > dp )
        {
                damage = 0;
                if (me->query_skill("blade") > target->query_skill("force") &&
                    query("reborn/times", me) >= query("reborn/times", target) && random(md)>ly )
                {
                        addn("neili", -100, me);
                        msg += HIR "当$n" HIR "感到$N" HIR "出手时，" + weapon->name() + HIR "早已挥出，化作满月时的月光，划过两丈的虚空劈向$n。\n"
                               "$n" HIR "只感到周遭所有的气流和生气都似被$N" HIR "这惊天动地的一招吸个一丝不剩，一派生机尽绝，\n"
                               "死亡和肃杀的骇人味儿。只听得轻轻的一声响，那道弯弯的刀光却还在，又弯弯地一转。然后美如月光的刀气消失了，\n"
                               "所有的声音都沉寂，所有的动作都停顿。$N" HIR "还是像一瞬前那么样静静地站在那里，好像根本没有动过。可是$N"
                               HIR "手里的" + weapon->name() + HIR "已经在滴着血。\n" NOR;
                        damage = -1;
                } else
                {
                        addn("neili", -600, me);
                        damage = damage_power(me, "blade");
                        damage+= me->query_all_buff("damage");
                        damage+= query("jiali", me);
                        damage+= damage / 300 * me->query_str();
                        damage+= damage * (fmsk/100)* 5 / 100;
                        damage+= damage/5;
                        
                        delta2 = ABILITY_D->check_ability(me, "da_power-yywd-ting"); // 门派ab
                        if( delta2 ) damage += damage*delta2/100;
        
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300,
                                                   HIR "结果$p" HIR "闪避不及，只觉得"
                                                   "一股冰寒的刀气掠过全身，$n全身顿时鲜血淋漓！\n" NOR);
                }
        } else
        {
                
                addn("neili", -300, me);
                msg += CYN "可是$p" CYN "识破了$P"
                       CYN "这一招，斜斜一跃避开。\n" NOR;
        }
        message_combatd(msg, me, target);
        me->start_busy(4);
        if (damage < 0)
                target->die(me);
                        
        if( userp(me) )
        {
                    if( BUFF_D->get_buff_overtime(me, "yywd_ting") > 0 ) 
                    {
                            return 1;
                    }
        }
        if( fmsk >= 1000 && query("neili", me)>1000 && sizeof(obs = me->query_enemy()) )
        {
                msg = HIC "\n====================" HIY" 魔" HIR "  吞" HIG "  天" HIW "  下" HIC " ====================" NOR;
                msg += HIC "\n猛然间，$N" HIC "手中" + weapon->name() + HIC +
                           "发出震天般的长啸，伴随着九幽魔气涌至天际，但见天云突变，\n转眼间，幻化出魔头张开大嘴，吞噬一切。\n" NOR;
                
                
                message_combatd(msg, me, 0, obs);
                for (flag = 0, i = 0; i < sizeof(obs); i++)
                {
                        if( !obs[i] ) continue;
                        dp = defense_power(obs[i], "parry") + obs[i]->query_skill("taoism", 1);
        
                        if (ap / 2 + random(ap)  + fmsk > dp)
                        {
                                damage = damage_power(me, "blade");
                                damage+= me->query_all_buff("damage");
                                damage+= query("jiali", me);
                                damage+= damage / 300 * me->query_str();
                                                                damage*= 3;
                                damage+= damage * (fmsk/100)* 5 / 100;
                                damage+= random(damage);
                                if( delta2 ) damage += damage*delta2/100;
                                if( wiz_level(me) > 2) tell_object(me,"damage = "+damage+"\n");
                                obs[i]->receive_damage("qi", damage, me);
                                obs[i]->receive_wound("qi", damage, me);
                                obs[i]->receive_damage("jing", damage*6, me);
                                obs[i]->receive_wound("jing", damage*3, me);                                                        
                                tell_object(obs[i], HIR "你刹那间目瞪口呆，全然无法相信"
                                           "眼前之景象，顿时被一招命中，射出无数柱鲜"
                                           "血。\n" NOR);
                                addn("neili", -500, me);
                                flag = 1;
                                p=query("qi", obs[i])*100/query("max_qi", obs[i]);
                                switch (random(3))
                                {
                                case 0:
                                msg = HIR "只见" + obs[i]->name() +
                                      HIR "手舞足蹈，忘乎所以，忽"
                                      "然大叫一声，吐血不止！\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                
                                break;
                                case 1:
                                msg = HIR "却见" + obs[i]->name() +
                                      HIR "容貌哀戚，似乎想起了什"
                                      "么伤心之事，身子一晃，呕出数口鲜血！\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;
                                default:
                                msg = HIR + obs[i]->name() +
                                      HIR "呆立当场，一动不动，有如中"
                                      "邪，七窍都迸出鲜血来。\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;
                                }
                                message("vision", msg, environment(me), ({ obs[i] }));
                                if (! obs[i]->is_busy())
                                        obs[i]->start_busy(3 + random(3));
                        } else
                        {
                                tell_object(obs[i], HIC "你发现眼前的景物似幻似真，连忙"
                                            "默运内功，不受困扰。\n" NOR);
                                addn("neili", -200, obs[i]);
                        }
                        if( query("neili", obs[i])<0 )
                                set("neili", 0, obs[i]);
                }
                
                if( !flag )
                        message_combatd(HIM "然而没有任何人受了$N"
                               HIM "的影响。\n\n" NOR, me, 0, obs);
        }
        time  = 40;
        time -= ABILITY_D->check_ability(me, "cd-yywd-ting"); // ab门派减cd 
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd
        if( wiz_level(me) > 2) time = 2;
           buff =
           ([ 
                   "caster" : me,
                   "target" : me,
                   "type"   : "cooldown",
                   "type2"  : "yywd_ting", 
                   "attr"   : "curse",
                   "name"   : "圆月弯刀·听春雨",
                   "time"   : time,
                   "buff_msg" : "小楼一夜听春雨消耗心神太甚，还需等待"+time+"秒方可再次施展。\n", 
                   "disa_msg" : "", 
                   "disa_type": 0,
           ]);
           BUFF_D->buffup(buff);
        return 1;
}

