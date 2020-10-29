#include <ansi.h>
#include <combat.h>

string name() { return HIM "散花天女" NOR; }
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        int ap, dp, damage;
        string pmsg;
        string msg;
        object weapon;
        int delta;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) ||
            (query("id", weapon) != "sanhua tianyu" &&
            query("skill_type", weapon) != "throwing") )
                return notify_fail("你现在手中没有拿着暗器散花天女，难以施展" + name() + "。\n");

        if( query("id", weapon) != "sanhua tianyu" &&
             weapon->query_amount() < 10)
                return notify_fail("你现在手中没有足够的暗器，难以施展" + name() + "。\n");

        if ((skill = me->query_skill("tangmen-throwing", 1)) < 160)
                return notify_fail("你的唐门暗器不够娴熟，难以施展" + name() + "。\n");

        if( query("tangmen/yanli", me)<80 )
                return notify_fail("你的眼力太差了，目标不精确，无法施展" + name() + "。\n");

        if ((int)me->query_skill("boyun-suowu", 1) < 160)
                return notify_fail("你的拨云锁雾不够娴熟，无法施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的内功修为不足，难以施展" + name() + "。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你现在真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        addn("neili", -100, me);

        msg = HIG "$N" HIG "手中扣住一枚" + weapon->name() + HIG"，不理敌人的攻击，身体急速旋转起来，犹如一道呼啸的旋风！\n" NOR
              HIG "突然从旋风中飞出无数点" HIC "寒星" NOR + HIG "，划出一道道长虹闪电般的飞向$n" HIG "的身体！\n" NOR;

        ap = attack_power(me, "throwing") +
             attack_power(me, "force");
        dp = defense_power(target, "parry") +
             defense_power(target, "dodge") +
             target->query_skill("dugu-jiujian", 1);
        
        delta = ABILITY_D->check_ability(me, "ap_power-tmaq-san"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        message_combatd(msg, me, target);
        tell_object(target, HIR "\n你急忙屏气凝神，希望能够招架这致命的一击。\n"NOR);
//        if (ap * 11 / 20 + random(ap / 2) > dp)
        if (ap / 2 + random(ap*4/3) > dp)
        {
                if( query("id", weapon) != "sanhua tianyu" )
                {
                        n = 10;
                        weapon->add_amount(-10);
                        damage = damage_power(me, "throwing");
                        damage+= query("jiali", me);
                        
                        delta = ABILITY_D->check_ability(me, "da_power-tmaq-san"); // 门派ab
                        if( delta ) damage += damage*delta/100;
        
                        msg = HIR "结果$p" HIR "一声惨嚎，连中了$P" HIR "发出的十" +
                                query("base_unit", weapon)+weapon->name()+HIR"。\n"NOR;

                        while (n--)
                        {
                                COMBAT_D->clear_ahinfo();
                                weapon->hit_ob(me, target,
                                               query("jiali", me)+100+n*10);
                        }

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage/2, me);

                        p=query("qi", target)*100/query("max_qi", target);

                        if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                                msg += pmsg;

                        msg += "( $n" + eff_status_msg(p) + " )\n";
                        message_combatd(msg, me, target);
                        me->start_busy(2);
                        return 1;
                }
                msg = HIR "忽然那无数的光影一闪而没，$n身行一顿，喷出一口鲜血，仰天而倒。\n" NOR;
                message_combatd(msg, me, target);
                tell_object(target, HIR "你只觉得胸口一阵钻心的疼痛。低头一看只见那无数枚暗器已经深深的嵌在你的心口。\n"
                                    "血迹中隐约有几个小字[散化天雨...]。\n"NOR);
                weapon->hit_ob(me,target,query("jiali", me)+200);
                if( !weapon->is_item_make() ) 
                weapon->move(target);

                target->receive_wound("qi", 100, me);
                COMBAT_D->clear_ahinfo();
                target->die(me);
                me->start_busy(2);
        } else
        {
                tell_object(target, HIR "忽然那无数的光影一闪而没，你心中一惊急忙运内力于全身。\n" NOR);
                msg = HIR "$n" HIR "双臂急舞，衣袖带起破风之声。只听当的一声轻响，竟将那无数枚暗器磕飞开去。\n" NOR;
                message_combatd(msg, me, target);
                if( query("neili", target)<1000 )
                        set("neili", 0, target);
                else
                        addn("neili", -1000, target);
                if( !weapon->is_item_make() ) 
                weapon->move(environment(me));
                me->start_busy(3);
        }
        return 1;
}

