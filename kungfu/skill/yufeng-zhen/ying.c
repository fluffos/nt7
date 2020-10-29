#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "无影针" NOR; }

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int skill, i;
        int n;
        int my_exp, ob_exp, p, damage;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) ||
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你现在手中并没有拿着针，怎么施展" + name() + "？\n");

        if (weapon->query_amount() < 1)
                return notify_fail("你手中没有针，无法施展" + name() + "。\n");

        if ((skill = me->query_skill("yufeng-zhen", 1)) < 100)
                return notify_fail("你的玉蜂针手法不够娴熟，不会使用" + name() + "。\n");

        if (me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够，无法施展" + name() + "。\n");

        if (me->query_skill_mapped("throwing") != "yufeng-zhen")
                return notify_fail("你没有激发玉蜂针，不能使用" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你内力不够，无法施展" + name() + "\n");

        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        addn("neili", -80, me);
        weapon->add_amount(-1);

        msg = HIY "$N" HIY "身不慌，足不移，手掌只是轻轻一抖，只见"
             "一点寒光闪过，闪电般的射向$n" HIY "！\n" NOR;

        me->start_busy(2);

        my_exp = attack_power(me, "throwing");

        ob_exp = defense_power(target, "dodge");

        if (my_exp / 2 + random(my_exp) > ob_exp)
        {
                damage = damage_power(me, "throwing");
                msg += HIR "结果$p" HIR "反应不及，中了$P" + HIR "一" +
                       query("base_unit", weapon)+weapon->name()+
                       HIR "！\n" NOR;
                target->receive_wound("qi", damage/2, me);

                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me,target,query("jiali", me)+100);

                p=query("qi", target)*100/query("max_qi", target);

                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;

                msg += "( $n" + eff_status_msg(p) + " )\n";

                message_combatd(msg, me, target);
        } else
        {
                msg += HIG "可是$p" HIG "从容不迫，轻巧的闪过了$P" HIG "发出的" +
                       weapon->name() + HIG "。\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}