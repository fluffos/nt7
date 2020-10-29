#include <ansi.h>
#include <combat.h>

string name() { return HIB "剑闪惊雷" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage,ran, ndam;
        string sexs;

        if (! target) target = offensive_target(me);
        
        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "只能在战斗中对对手使用。\n");
        
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" +name()+ "。\n");
        
        if (me->query_skill("lunhui-sword", 1) < 1200)
                return notify_fail("你的六道轮回剑修为不够，难以施展" +name()+ "。\n");
        
        if (me->query_skill_mapped("sword") != "lunhui-sword")
                return notify_fail("你没有激发六道轮回剑，难以施展" +name()+ "。\n");
        
        if (me->query_skill_mapped("sword") != "lunhui-sword")
                return notify_fail("你没有激发六道轮回剑，难以施展" +name()+ "。\n");
        
        if( query("neili", me)<3000 )
                return notify_fail("你的真气不够，难以施展" +name()+ "。\n");
        
        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
        msg = HIC "$N" HIC "轻啸一声，手中" + weapon->name() + HIC "平平一剑刺出，速度之快，有如电闪雷鸣一般！\n" NOR;
        
        ap=me->query_skill("sword")+query("force", me)+me->query_skill("martial-cognize",1);
        dp=target->query_skill("parry")+query("force", target)+target->query_skill("martial-cognize",1);
        
        if (1)
        {
                damage = ap / 4 + random(ap / 3);
                //damage += weapon->apply_damage(); // 追加一次武器的伤害
                addn("neili", -3000, me);
                me->start_busy(3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75,
                                           HIR "只听$n" HIR "一声惨叫，$N" HIR +
                                           weapon->name() + HIR "剑过之处，一道蓝色电光射"
                                           "入$p" HIR "体内。\n"
                                           NOR);
                
                // 追加一次武器伤害
                ran = 35;
                ndam = 10;
                if (me->query_skill("lunhui-sword", 1) >= 5000)
                {
                        ran = 100;
                        ndam = 5;
                }
                else if (me->query_skill("lunhui-sword", 1) >= 4000)
                {
                        ndam = 7;
                }
                else if (me->query_skill("lunhui-sword", 1) >= 3000)
                {
                        ran = 75;
                }
                else if (me->query_skill("lunhui-sword", 1) >= 2000)
                {
                        ran = 50;
                }
                // 追加一次武器伤害
                if (random(100) < ran || wizardp(me))
                {
                        msg = msg + HIG + weapon->name() + HIG "发出雷鸣般的响声，伴随着一道剑光再次穿透" +
                              target->name() + HIG "身体……\n" NOR +
                              HIR "一股鲜血顺着" + weapon->name() + HIR "喷射而出！\n" NOR;
                        target->receive_damage("qi", weapon->apply_damage() / 2, me);
                        target->receive_wound("qi", weapon->apply_damage() / 2, me);
                }
        
                if( !query_temp("lunhui-sword/jinglei", target) )
                {
                        // 第一次直接10%最大气血伤害
                        target->receive_damage("qi",query("max_qi", target)/ndam,me);
                        target->receive_wound("qi",query("max_qi", target)/ndam,me);
                        msg = msg + target->name() +  HIM "闷哼一声，鲜血喷出，看来是受到了这一剑的剑气所伤。\n" NOR;
                        set_temp("lunhui-sword/jinglei", 1, target);
                }
        } else
        {
                addn("neili", -1000, me);
                me->start_busy(4);
                msg += CYN "$n" CYN "见$P" CYN "来势汹涌，不敢轻易抵"
                       "挡，连忙飞身腾挪，躲闪开来。\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        
        return 1;
}

