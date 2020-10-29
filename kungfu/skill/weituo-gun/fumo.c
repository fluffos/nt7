// This program is a part of NITAN MudLIB
// fumo.c 韦托伏魔

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "韦托伏魔"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「韦托伏魔」只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的内功的修为不够，难以使用这一绝技！\n");

        if (me->query_skill("weituo-gun", 1) < 135)
                return notify_fail("你的韦陀棍法修为不够，目前不能使用韦托伏魔！\n");

        if( query("neili", me)<800 )
                return notify_fail("你的真气不够，不能使用韦托伏魔！\n");

        if (me->query_skill_mapped("club") != "weituo-gun")
                return notify_fail("你没有激发韦陀棍法，不能使用韦托伏魔！\n");

        if( query("shen", me)<10000 )
                return notify_fail("你正气不足，难以理解韦托伏魔的精髓。\n");

        msg = HIY "$N" HIY "脸色柔和，尽显一派慈祥之意，手中的" + weapon->name() +
              HIY "轻旋，恍惚中显出佛家韦陀神像，神光四射，笼罩住$n" + HIY "！\n" NOR;

        if (target->is_bad())
        {
                ap=query("shen", me)/1000;
                if (ap > 1000) ap = (ap - 1000) / 4 + 1000;
                if (ap > 2000) ap = (ap - 2000) / 4 + 2000;
                if (ap > 3000) ap = (ap - 3000) / 4 + 3000;
                if (ap > 5000) ap = 5000;
                msg += HIR "$n" HIR "平日作恶不少，见了此情此景，心中不禁颤然！\n" NOR;
        } else
                ap = 0;

        ap += attack_power(me, "club");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "club");
                damage+= query("jiali", me);
                addn("neili", -500, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           HIR "结果只听$p" HIR "一声惨叫，被$P"
                                           "一下子打中要害，七窍一起生烟，耳鼻都渗出血来！\n" NOR);
                me->start_busy(1 + random(2));

        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "强摄心神，没有被$P"
                       CYN "所迷惑，硬生生的架住了$P" CYN "这一招！\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}