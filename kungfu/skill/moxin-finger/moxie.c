// This is player's own perform (Write by Lonely@nt2)
// Create by 枯枝(Kuzhi) at Wed May 27 02:38:43 2015
// 魔邪翻天(moxie)
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int is_player_perform() { return 1; }

string name() { return HIW "魔邪翻天" NOR; }

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

        if (member_array("finger", weapon_sk) != -1)
        {
                attack = WEAPON_ATTACK;
                if( !objectp(weapon=query_temp("weapon", me) )
                    || query("skill_type", weapon) != "finger" )
                        return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");
        } else
        {
                attack = UNARMED_ATTACK;
                if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                        return notify_fail(name() + "只能空手使用。\n");
        }

        if ((int)me->query_skill("moxin-finger", 1) < 400)
                return notify_fail("你" + to_chinese("moxin-finger") + "不够娴熟，难以施展" + name() + "。\n");

        if (member_array("finger", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("finger") != "moxin-finger")
                        return notify_fail("你没有准备" + to_chinese("moxin-finger") + "，难以施展" + name() + "。\n");
        }

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N指劲飞出，铺天盖地，完全拨反了防御百丈内一切事物的运行方向。向前变成向后，向左变成向右，向上变成向下，向外变成向内，天地万物运转，全部反其道而行之，$n整个人都感觉不好了！" + "\n" + NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = damage_power(me, "finger")*9;
                msg += COMBAT_D->do_damage(me, target, attack, damage, 490, HIM "结果$n闪避不及，$N的指劲顿时透体而入，整个人原地乱转，口中鲜血狂喷，连退百步。" + "\n" NOR);
                addn("neili", -200, me);
                me->start_busy(1);
                /*
                if (! target->is_busy())
                        target->start_busy(2);
                */
        } else
        {
                msg += NOR + CYN "$p见势不妙，运气凝神一动都不敢动，硬是抗过$P的这记杀招，看着身旁逆转的一切，深深的吸了一口冷气！" + "\n" NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }

        message_sort(msg, me, target);
        return 1;
}
