// This program is a part of NT MudLIB
// qi.c 无形剑气

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "无形剑气" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;
        int n;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("force") < 420)
                return notify_fail("你的内功火候不够，使不出" + name() + "。\n");

        if( query("max_neili", me) < 5000 )
                return notify_fail("你的内力修为还不足以使出如此犀利的" + name() + "。\n");

        if( query("neili", me) < 500 )
                return notify_fail("你的真气不够，无法使用" + name() + "。\n");

        if (me->query_skill("six-finger", 1) < 200)
                return notify_fail("你的六脉神剑修为有限，无法使用" + name() + "！\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("你没有准备六脉神剑，无法使用" + name() + "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIG "$N" HIG "中指一按，一股凌厉无伦的无形剑气直奔$n" HIG "胸前射去。\n" NOR;

        ap = attack_power(me, "finger")+me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");
        weapon=query_temp("weapon", target);
        me->start_busy(3);
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                {
                        msg += HIM"$N"HIM"运用气脉流转的辅助，使得无形剑气伤害更强。\n"NOR;
                        damage += damage*n*15/100;
                }
                addn("neili", -400, me);
                if( !objectp(weapon) || query("skill_type", weapon) == "pin" )
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
                                                   HIR "$n" HIR "只觉得胸前一阵剧痛，鲜血"
                                                   "自创口激射而出，眼前顿时一黑！\n" NOR);
                else
                if( weapon->is_item_make() || query("damage", weapon)>180 ||
                    query("skill_type", weapon) == "hammer" )
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100,
                                                   HIR "$n" HIR "横" + weapon->name() + HIR "试图招架，"
                                                   HIR "怎奈这股剑气如此犀利，透过" + weapon->name() +
                                                   HIR "直震得$n" HIR "狂吐鲜血，五脏六腑都要翻转过来！\n" NOR);
                else
                {
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 80,
                                                   HIR "$n" HIR "横转" + weapon->name() + HIR "，挡在胸"
                                                   "前，只听啪啦一声，" + weapon->name() +
                                                   HIR "碎成数截，激飞上天！\n$n" HIR "连退"
                                                   "几步，“哇”的吐了一口鲜血，脸色变的惨白。\n" NOR);
                        weapon->move(environment(me));
                        set("no_wield", weapon->name()+"已经碎掉了，没法装备了。\n", weapon);
                        weapon->set_name("碎掉的" + weapon->name());
                        set("value", 0, weapon);
                }
        } else
        {
                msg += CYN "可是$p" CYN "内功颇为深厚，轻轻将这道剑气化解于无形。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
