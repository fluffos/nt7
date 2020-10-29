// This is player's own perform (Write by Lonely@nt2)
//Createby虚宁(Ningbufan)atTue May 10 12:50:25 2011
// 仁剑震音扬(renjian)
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "仁剑震音扬" NOR; }

string *weapon_sk = ({
        "sword", "blade", "staff", "whip", "club", "hammer", "axe"
});

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int attack;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (member_array("sword", weapon_sk) != -1)
        {
                attack = WEAPON_ATTACK;
                if( !objectp(weapon=query_temp("weapon", me) )
                    || query("skill_type", weapon) != "sword" )
                        return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");
        } else
        {
                attack = UNARMED_ATTACK;
                if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                        return notify_fail(name() + "只能空手使用。\n");
        }

        if ((int)me->query_skill("sanda-sword", 1) < 400)
                return notify_fail("你" + to_chinese("sanda-sword") + "不够娴熟，难以施展" + name() + "。\n");

        if (member_array("sword", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("sword") != "sanda-sword")
                        return notify_fail("你没有准备" + to_chinese("sanda-sword") + "，难以施展" + name() + "。\n");
        }

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N面露悲悯，双脚站立不动，剑柄抵住额头，口中念念有辞，持剑如持香，只见$N两手掌心向外，以黏劲吸住剑柄，内力发动，剑刃旋转如盘，望之如同月轮。这剑转动快速劲急，却不闻分毫破空之声，金轮盖顶，热气飘荡，彷佛佛顶光晕一般，便在此时，那光晕往外膨胀，登将$n整个人包在圈内" + "\n" + NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, attack, damage, 90, HIM "只听叮叮当当之声不绝于耳，无数断剑已然跌落地面，一声惨嚎，跟着$n口吐鲜血，跪倒在地。" + "\n" NOR);
                addn("neili", -200, me);
                me->start_busy(1);
                /*
                if (! target->is_busy())
                        target->start_busy(2);
                */
        } else
        {
                msg += NOR + CYN "$p见势不妙，抽身急退，险险避过$P的这记杀招，尘土飞扬中，地上裂开了一道大口子！" + "\n" NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }

        message_sort(msg, me, target);
        return 1;
}
