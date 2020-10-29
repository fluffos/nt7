// mie.c  回风拂柳剑法「灭剑」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "灭剑" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp;
        int lvl_jingxin;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不对，无法施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "huifeng-jian")
                return notify_fail("你没有激发回风拂柳剑法，无法施展" + name() + "。\n");

        if ((int)me->query_skill("huifeng-jian", 1) < 120)
                return notify_fail("你的回风拂柳剑法不够娴熟，无法施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的内功火候不够，无法施展" + name() + "。\n");

        if( query("neili", me)<500 )
               return notify_fail("你现在真气不够，无法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "手中长剑剑芒跃动，剑光暴长，幻出死亡的色彩，剑尖渐"
              "渐逼近$n" HIR "，\n$n" HIR "看到漫天剑光，抽身后跃，可是只这一刹"
              "，$N" HIR "漫天剑影化为一剑直\n刺$n" HIR "前胸，快捷无伦，只有一"
              "剑！\n" NOR;

        lvl_jingxin = me->query_skill("jingxin", 1);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");
        ap = ap + ap *  lvl_jingxin / 500;
        
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "sword");
                damage += query("jiali", me);
                damage += damage;
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80+lvl_jingxin/15,
                                           HIR "$n" HIR "全然无法躲避，" + weapon->name() +
                                           HIR "端端正正扎进在$p" HIR "的胸口，鲜血登时飞溅"
                                           "而出。\n" NOR);
                addn("neili", -150, me);
        } else
        {
                me->start_busy(3);
                msg += YEL "可是$p" YEL "轻轻一笑，侧身右转，伸"
                       "出两指，正弹在$P" YEL "的剑上，" + weapon->name() +
                       YEL "在$p" YEL "身侧划过，有惊无险。\n"NOR;
                addn("neili", -60, me);
        }
        message_combatd(msg, me, target);
        return 1;
}
