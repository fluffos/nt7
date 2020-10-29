// jianqi.c 六道轮回

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        string *learned;
        object weapon, weapon2;
        string type,perform_type;
        mapping prepare;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("liudaolunhui-sword", 1);

        if (! me->is_fighting(target))
                return notify_fail("六道轮回剑气只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("sword") != "liudaolunhui-sword") 
                return notify_fail("你没有用六道轮回剑法，无法使用剑气绝招！\n");

        if (skill < 100)
                return notify_fail("你的六道轮回剑法等级不够，练好了再来！\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够。\n");
        
        ap = me->query_skill("sword") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIG "$N" HIG "凝神静气，默运神通，周围寒气渐生，手中" + weapon->name() + HIG
              "通体碧寒，仿佛周围一切都已经被冻结了。\n" NOR;

        msg += HIY "$N" HIY "乘$n" HIY "气血僵硬，无法动弹之际，手中" + weapon->name() + HIY
              "剑走偏锋，笼罩$n" HIY "全身各处大穴，顺势连出数招。\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg = HIW "忽然$N" HIW "大喝一声，" + weapon->name() + HIW
                      "遥遥指向$n。\n" HIW "一道剑气如白色蛟龙般汹涌喷薄，带着周围刺骨的寒气袭向$n" HIW "的全身。\n" + 
                      "待得$n" HIW "猛然惊觉，却为时已晚。" HIR "剑气" HIW "已透体而过，全身气血凝固，仿佛被冻僵了！\n" NOR;

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg = HIW "$N" HIW "抖动着手中的" + weapon->name() + HIW "寻找着机会，"
                      "可是$n" HIW "拼命躲闪，$N" HIW "一时竟也无机可乘。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
        addn("neili", -damage/3, me);
        return 1;
}

