#include <ansi.h>
#include <combat.h>

string name() { return HIR "唐花" NOR; }

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        int ap, dp, damage;
        string msg;
        object weapon;
        int delta;
        int fmsk = me->query_skill("luoxian-jue", 1);

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
                (query("id", weapon) != "tang hua" &&
                query("skill_type", weapon) != "throwing") )
                return notify_fail("你现在手中没有拿着暗器唐花，难以施展" + name() + "。\n");

        if ((skill = me->query_skill("tangmen-throwing", 1)) < 180)
                return notify_fail("你的唐门暗器不够娴熟，难以施展" + name() + "。\n");

        /*
        if( query("tangmen/yanli", me)<80 )
                return notify_fail("你的眼力太差了，目标不精确，无法施展" + name() + "。\n");
        */

        if ((int)me->query_skill("boyun-suowu", 1) < 180)
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

        msg = HIR "\n$N" HIR "手中突然多了一支花，美得妖艳，$n" HIR "觉得有点痴了，\n$N" HIR "向$n" HIR "一笑，一扬手向$n"HIR "抛去。\n" +
              HIG "只见那花开了，五瓣齐舒，中央花心吐蕊，煞是好看。\n" NOR;

        ap = attack_power(me, "throwing") * 2;
        dp = defense_power(target, "parry") + defense_power(target, "dodge") +
             target->query_skill("lonely-sword", 1) * 25;

        delta = ABILITY_D->check_ability(me, "ap_power-tmaq-hua"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        ap += ap * (fmsk / 100) * 5 / 100;
        message_combatd(msg, me, target);
        tell_object(target, HIC "\n你急忙伸出手去接，但突地，你发现有异，那是一朵铁花，纵身一跃。\n" NOR);
//        if (ap * 2 / 3 + random(ap * 3 / 2) > dp)

if (playerp(target) || !random(40)) { //pvp或极小的几率，需要有门派能稍稍克制唐门，by redl
    if ( BUFF_D->check_buff(target, "qkdny-nuozhuan") && (random(me->query_skill("tangmen-throwing", 1)) < target->query_skill("qiankun-danuoyi", 1) /2) ) {
        message_combatd(HIY "$n运转" MAG "挪转乾坤" NOR HIY "，$N发出的暗器速度随之一滞。\n" NOR , me, target); 
        ap -= ap / 4; 
    }
}

        if (ap / 2 + random(ap*4/3) > dp)
        {
                if( (fmsk < 1000 && (query("yuanshen", target) || query("id", weapon) != "tang hua")) || (playerp(target) && !random(8)) )
                {
                        string pmsg;

                        weapon->add_amount(-1);
                        damage = damage_power(me, "throwing");
                        damage+= query("jiali", me);
                        damage*=2;
                        delta = ABILITY_D->check_ability(me, "da_power-tmaq-hua"); // 门派ab
                        if( delta ) damage += damage*delta/100;
                        damage += damage * (fmsk/100) * 5 / 100; 
        
                        msg = HIR "结果$p" HIR "一声惨嚎，连中了$P" HIR "发出的一" +
                                query("base_unit", weapon)+weapon->name()+HIR"。\n"NOR;

                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me,target,query("jiali", me)+120);

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage, me);

                        p=query("qi", target)*100/query("max_qi", target);

                        if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                                msg += pmsg;

                        msg += "( $n" + eff_status_msg(p) + " )\n";
                        message_combatd(msg, me, target);
                        me->start_busy(2);
                        return 1;
                }

                msg = HIR"那花越开越艳，$n" HIR "不知不觉中已痴迷了，身形一慢,微笑着倒下了，那花也谢了。\n" NOR;
                tell_object(target, HIR "\n你看到那花，果真是一朵铁花。\n你慢慢的伸出手想摘下它，但"
                                        "那花好象变的越来越多了，依稀中你记得那上面有一个小小的“唐”字。\n" NOR);
                weapon->hit_ob(me,target,query("jiali", me)+200);
                if( !weapon->is_item_make() )
                weapon->move(target);

                message_combatd(msg, me, target);
                target->receive_wound("qi", 100, me);
                COMBAT_D->clear_ahinfo();
                target->unconcious(me);
                me->start_busy(2);
        } else
        {
                if( query("id", weapon) == "tang hua" )
                        tell_object(target, HIR "果真是唐花，唐门中的唐花。你运足全身的内力，身形掠的更急。\n" NOR);
                msg = HIR "$n " HIR "身形飘忽，那花划空而过。只听当的一声轻响，那花谢了，轻轻地砸在地面上。\n" NOR;
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

