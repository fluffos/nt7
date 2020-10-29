#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIM "万剑纵横" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage, skill;
        int n;
        int delta;
        int fmsk = me->query_skill("qimai-liuzhuan", 1);

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("你没有准备使用六脉神剑，无法施展" + name() + "。\n");

        skill = me->query_skill("six-finger", 1);

        if (skill < 260)
                return notify_fail("你的六脉神剑修为有限，无法使用" + name() + "！\n");

        if (me->query_skill("force") < 480)
                return notify_fail("你的内功火候不够，难以施展" + name() + "！\n");

        if( query("max_neili", me)<5500 )
                return notify_fail("你的内力修为不够,无法施展" + name() + "！\n");

        if( query("neili", me)<850 )
                return notify_fail("你的真气不够，现在无法施展" + name() + "！\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必须是空手才能施展" + name() + "！\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");


        msg = HIM "$N" HIM "一声清啸，十指纷弹，顿觉六脉剑谱已涌上心头，此起"
              "彼伏、连绵不绝。霎时剑气如奔，连绵无尽的万道剑气豁然贯向$n" HIM
              "！\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");
        
        delta = ABILITY_D->check_ability(me, "ap_power-lmsj-zong"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        if (target->query_skill("martial-cognize", 1) >= 800 && (int)target->query_skill("jingluo-xue", 1) >= 200 
            && random (100) == 1 )
        {
                addn("neili", -600, me);
                me->start_busy(3);
                msg += HIY "但见$n" HIY "会心一笑，轻拂衣袖，轻易的躲过这一招！\n"NOR;
        } else
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                
                delta = ABILITY_D->check_ability(me, "da_power-lmsj-zong"); // 门派ab
                if( delta ) damage += damage*delta/100;
                damage *= 3;
        
                if( (n = fmsk / 100) >= 1 )
                {
                        damage += damage*n*15/100;
                        msg += HIM"$N"HIM"运用气脉流转的辅助，使得万剑纵横伤害更强。\n"NOR;
                }
                addn("neili", -800, me);
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 200+random(100),
                                           HIR "只听$n" HIR "一声惨叫，万道剑气已"
                                           "透体而过，伤口处鲜血顿时狂涌，痛苦难当！\n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", -400, me);
                me->start_busy(3);
                msg += CYN "$n" CYN "见$N" CYN "来势汹涌，不敢轻易"
                       "招架，急忙提气跃开。\n" NOR;
        }
        message_sort(msg, me, target);

        return 1;
}

