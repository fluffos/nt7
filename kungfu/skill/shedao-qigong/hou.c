// 唱仙法吼字决

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "吼字决"; }
int perform(object me, object target)
{
        string msg;
        int neili, damage;
        int i;
        int ap, dp;
        int fmsk = me->query_skill("mukong-yiqie", 1);
        int delta;

        if (! target ) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("唱仙法吼字决只能在战斗中对对手使用。\n");

        if ((int)me->query_skill("shedao-qigong", 1) < 100)
                return notify_fail("你的蛇岛奇功不够娴熟，不会使用唱仙法吼字决。\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("在这里不能攻击他人。\n");

        if( query("neili", me)<500 )
                return notify_fail("你已经精疲力竭，真气不够了。\n");

        if (me->query_skill_mapped("unarmed") != "shedao-qigong")
                return notify_fail("你没有将基本拳脚"
                                   "激发为蛇岛奇功, 不能使用「吼字决」！\n");

        //neili=query("max_neili", me);
        neili=query("neili", me);
        if( neili > query("max_neili", me)*2 )
                neili = query("max_neili", me) * 2;

        addn("neili", -(300+random(200)), me);
        me->receive_damage("qi", 10);

        // me->start_busy(1 + random(5));

        message_combatd(HIY "$N" HIY "深深地吸一囗气，忽然仰天长啸，高"
                        "声狂叫：不死神龙，唯我不败！\n" NOR, me);

        if( neili/2+random(neili/2)<query("max_neili", target) )
                return notify_fail("敌人的内力不逊于你，伤不了！\n");

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "force");
        
        delta = ABILITY_D->check_ability(me, "ap_power-sdqg-xian"); // 门派ab
        if( delta ) ap += ap*delta/100;
                
        msg = "";
        if (ap / 2 + random(ap) > dp)
        {
                damage=(neili-query("max_neili", target))/2;
                if (damage > 0)
                {
                        damage+= query("jiali", me);
                        target->receive_damage("jing", damage, me);
                        target->receive_damage("qi", damage, me);
                        target->receive_wound("jing", damage / 4, me);
                        target->receive_wound("qi", damage / 4, me);
                        message_combatd(HIR "$N" HIR "只觉脑中一阵剧痛，金星乱"
                                "冒，犹如有万条金龙在眼前舞动。\n" NOR, target);
                } else
                {
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        delta = ABILITY_D->check_ability(me, "da_power-sdqg-xian"); // 门派ab
                        if( delta ) damage += damage*delta/100;
                        
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60+fmsk/50,
                                           HIR "$n" HIR "只觉得$N" HIR "内力犹如"
                                           "排山倒海一般，怎能抵挡？“哇”的一下吐出一大口鲜血。\n" NOR);
                }
        } else
                msg += CYN "$n" CYN "哈哈一笑，飘身跃开，让$N"
                       CYN "这一吼全然落空。\n" NOR;

        message_combatd(msg, me, target);
        me->start_busy(2);
        /*
        me->want_kill(target);
        me->kill_ob(target);
        */
        return 1;
}