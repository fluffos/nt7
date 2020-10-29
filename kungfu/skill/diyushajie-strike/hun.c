// hun.c 群魔乱舞

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("diyushajie-strike", 1);

        if (! me->is_fighting(target))
                return notify_fail("群魔乱舞只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("strike") != "diyushajie-strike") 
                return notify_fail("你没有用地狱杀劫掌法，无法使用「群魔乱舞」绝招！\n");

        if (me->query_skill_prepared("strike") != "diyushajie-strike")
                return notify_fail("你没有准备使用地狱杀劫掌法，无法施展「群魔乱舞」绝招。\n");

        if (skill < 100)
                return notify_fail("你的地狱杀劫掌法等级不够，练好了再来！\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必须空着双手才能使用掌法绝招。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够。\n");
        
        ap = me->query_skill("strike") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIG "$N" HIG "双手合结“" HIY "十八层地狱轮回印" HIG "”，"
              "脚踏阴阳八卦阵,方圆十里群魔乱舞。\n" HIG "阵阵奇异的声音，犹如鬼吟，"
              "令$n" HIG "心神不定，神情恍惚。\n"
              "突然间一圈圈碧芒围向$n" HIG "，震得$n" HIR "吐血" HIG "连连！\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = HIG "\n$n" HIG "尚未回过心神，结果发现被“" HIY "十八层地狱轮回杀劫" HIG "”的强大魔气冲入体内，登感呼吸不畅。\n"
              "乘此良机，$N" HIG "十八股极大的力道如同排山倒海一般奔向$n" HIG "，周遭狂风大作，飞砂走石！\n\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIM "$n" HIM "再也抵挡不住，身子被高高抛起，口中" HIR "鲜血" HIM "狂喷，生死不明。\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIM "$n" HIM "拼力纵身后跃，险险避过此致命一击，心有余悸。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        addn("neili", -damage/3, me);
        return 1;
}

