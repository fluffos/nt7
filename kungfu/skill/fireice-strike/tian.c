// This program is a part of NT MudLIB
// binghuo.c 烈焰寒冰掌--

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "冰火二重天"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int damage, ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()
        ||  !me->is_fighting(target))
                return notify_fail("「冰火二重天」只能在战斗中使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("只有空手才能施展「冰火二重天」。\n");

        if( (int)me->query_skill("fireice-strike", 1) < 150 )
                return notify_fail("你的烈焰寒冰掌功夫还不够娴熟，不会使用「冰火二重天」。\n");

        if(me->query_skill("yunv-xinfa", 1) < 120)
                return notify_fail("以你现在的玉女心法还使不出「冰火二重天」。\n");

        if ( me->query_skill_mapped("strike") != "fireice-strike" )
                return notify_fail("你现在无法使用「冰火二重天」进行攻击。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的内力修为太弱，不能使用「冰火二重天」！\n");

        if( query("neili", me)<800 )
                return notify_fail("你的真气不够！\n");

        if( !living(target) )
                return notify_fail("对方已经这样了，用不着使这么大力气吧。\n");

        if ("jiuyang-shengong" == target->query_skill_mapped("force"))
        {
                msg = HIR"$N" HIR"左手手心隐隐透红光，一股炽热掌气向" HIR"$n" HIR"迎脸扑来！\n" NOR;

                dp = target->query_skill("force",1) / 4;

                if (random(me->query_skill("force",1)) > dp)
                {
                       addn("neili", -100, me);
                       msg += HIY "$n一见之下，暗运九阳神功作出抵抗！！脸色转了几转，安然无恙！\n"NOR;
                }  else
                {
                       me->start_busy(3);
                       addn("neili", -200, me);
                       msg += HIW"$p" HIW"大喝一声“来的正好！”猛运九阳真气，\n"
                              HIR"$N" HIR"的掌力竟被反震，血气翻腾！连退数步！\n"NOR;
                }
        }  else
        {
                msg = HIR "\n$N" HIR "左手手心隐隐透红光，一股炽热掌气直袭" HIR "$n" HIR "胸口！\n"NOR;

                ap = attack_power(me, "strike");
                dp = defense_power(target, "parry");
                if (ap / 2 + random(ap) > dp)
                {
                        //me->start_busy(1);
                        if( !target->is_busy() )
                                target->start_busy(1);

                        addn("neili", -300, me);
                        damage = damage_power(me, "strike");
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                HIR "$n" HIR" 顿时觉得胸口如被火烧，一口真气难以继回，!!\n"NOR);

                        if( me->query_skill("fireice-strike", 1) > 150 )
                                call_out("perform2", 0, me, target);
                }
                else
                {
                        me->start_busy(3);
                        addn("neili", -100, me);
                        msg += HIW"可是$p一个巧云翻身，远远的躲了开去。\n"NOR;
                }
        }
        message_combatd(msg, me, target);
        return 1;
}

int perform2(object me, object target)
{
        string msg;
        int damage, ap, dp;

        if (!me || !target || environment(me) != environment(target)) return 0;
        if(!living(target))
                return notify_fail("对手已经不能再战斗了。\n");

        if( query("neili", me)<600 )
                return notify_fail("你待要再出第二掌，却发现自己的内力不够了！\n");

        msg = HIB "\n接着" HIB "$N" HIB "你挥出右手，手心竟是暗隐寒劲，以巧妙角度向" HIB "$n" HIB "拍过去!\n"NOR;
        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);

                addn("neili", -300, me);
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                HIW  "结果一掌击中，" HIW "$n" HIW "只觉得全身气脉通道如遭冻结，脸色一下变白！\n"NOR);
        }
        else
        {
                me->start_busy(3);
                addn("neili", -100, me);
                msg += HIY "\n$p" HIY "眼看寒气逼人，暗生警觉，顺势跳了开去。\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
