#include <ansi.h>
#include <combat.h>

#define WSWD "「" HIR "无"BLU"双"HIM"无"HIW"对" NOR "」"
#define WS "「" HIR "无"BLU"双" NOR "」"
#define WD "「" HIM"无"HIW"对" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill = (int)me->query_skill("kuihua-mogong", 1), i;
        int ap, dp;
        int damage;
        int x,a;
        string msg,nextmsg;
        object weapon=query_temp("weapon", me);

        if( !target || target == me ) target = offensive_target(me);

        if( query("no_fight", environment(me)) )
                return notify_fail("这里不准打架。\n");

        if( me->is_busy()) return notify_fail("你正忙着呢。\n");

        if( userp(me) && !query("can_perform/kuihua-mogong/wswd", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if( !target || target==me || !target->is_character() )
                return notify_fail(WS"只能对对手使用。\n");

        if( !weapon
         || query("skill_type", weapon) != "sword"
        ||      me->query_skill_mapped("sword") != "kuihua-mogong" )
                return  notify_fail("你现在无法使用绝技。\n");

        if (skill < 200 || (int)me->query_skill("kuihua-mogong", 1) < 200)
                return notify_fail("以你目前的修为来看，还不足以运用"WS"\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力修为不够运用"WS"所需！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够运用"WS"所需！\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        me->start_busy(1 + random(3));
        msg = HIM "$N突然身形一转眨眼间使用葵花魔功的终极绝招----" NOR
                WSWD HIM "之" NOR WS "\n" HIW "$N眼神莹然有光，似乎进入了魔境之中。\n" +
                "$N手中" + weapon->name() + "化做无双剑影攻向$n。\n";
        ap=me->query_skill("kuihua-mogong",1)*1+query("dex", me)*20+
                me->query_skill("martial-cognize", 1);
        dp=target->query_skill("parry")+query("dex", target)*10+
                target->query_skill("martial-cognize", 1);

        me->start_busy(2);
        addn("neili", -400, me);

        if (ap / 2 + random(ap) < dp)
        {
            msg += HIG "然而$n" HIG "抵挡得法，将$N" HIG
                    "的攻势一一化解。\n" NOR;
        } else
        {
            addn("neili", -560, me);
            damage = ap * 2 + random(ap * 3 / 4) - 60 - random(40);
            msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                    HIY "$n" BLU "只觉得已经跌入了万劫魔域之中，" HIY
                    "$N手中" + weapon->name() + WHT
                    "如同地狱中的鬼火般，从各个方位刺了过来，避无可避！\n" NOR);
        }
        message_sort(msg, me, target);

        if( query("neili", me)>2000
         && present(query("id", target),environment(me) )
        &&  me->is_fighting(target)
        &&  target->is_fighting()
        &&  living(target)
        &&  living(me)
        &&  !target->is_ghost()
        &&  !me->is_ghost()
        &&  me->query_skill_mapped("sword") == "kuihua-mogong"
         && query("skill_type", weapon) == "sword"
         && (userp(me) && query("can_perform/kuihua-mogong/wd", me )
                || !userp(me))
                )
        {
                remove_call_out("perform2");
                call_out("perform2",0, me);
        }
        else if( userp(me) && !query("can_perform/kuihua-mogong/wd", me))//没学会无对
        {
                remove_call_out("check_wd");
                call_out("check_wd",1,me);
        }
        return 1;
}

int perform2(object me)
{
        int ap, dp;
        string nextmsg;
        int damage;
        object target;
        object weapon=query_temp("weapon", me);

        if( !target ) target = offensive_target(me);
        if( !target || living(target) )     return 1;
        if(!objectp(weapon)) return 1;

        nextmsg = HIM "说是迟那时快，$N身形逆转使出了" NOR WSWD "之" WD HIM
                "式，刹那间天空阴云密布，\n" NOR HIM "$n的心脏几乎停止了跳动，呆呆的望着$N\n" NOR;
        ap=me->query_skill("kuihua-mogong",1)*1+query("dex", me)*20+
        me->query_skill("martial-cognize", 1);
        dp=target->query_skill("parry")+query("dex", target)*8+
        target->query_skill("martial-cognize", 1);

        me->start_busy(2);
        addn("neili", -400, me);

        if ( ap / 2 + random(ap) < dp && !(target->is_busy()) )
        {
                nextmsg += HIG "这时$n屏住呼吸" HIG "抵挡得法，将$N" HIG
                        "的攻势一一化解。\n" NOR;
        } else
        {
                addn("neili", -260, me);
                damage = ap * 1 + random(ap * 1 / 5) - 60 - random(40);
                nextmsg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                        HIY "$n" BLU "只觉身上如同万剑穿心一般，" HIY "$N"
                        WHT "如同死神一般，势必要取$n性命！\n" NOR
                        HIM "此时此刻$N挥舞着手中" + weapon->name() + HIM
                        "，瞬间变化了几个剑招，可是$n就是无法找出破解之法，\n" +
                        "说时迟那时快" + weapon->name() + HIM
                        "已经刺进了$n的胸膛，鲜血溅了一地！！\n" NOR);
        }
        message_vision(nextmsg, me, target);
        return 1;
}

int check_wd(object me)
{
        int x,a;
        object target;

        x=query("kar", me);
        a = x + random(70);

        if( !target ) target = offensive_target(me);
        if(living(target))  return 1;
        if (me->is_fighting())  return 1;

        if(a>=80){
                tell_object(me,
                        HIW "\n你突然若有所悟，对刚才使用过的魔功之" WS
                        HIW "式反复琢磨，\n对了，这样也可以耶！你学会了" WSWD
                        HIW "之" WD HIW "式！\n" NOR);
                set("can_perform/kuihua-mogong/wd", 1, me);
        }
        return 1;
}
/*
    } else {
        msg += "$n邪邪的看着$N，不知不觉中$n表现出万分的恐惧。\n"NOR;
        msg += HIM"\n$N猛然想到了什么，$n立刻开始无限痛苦的呻吟起来！\n\n"NOR;

        ap=me->query_skill("kuihua-mogong",1)*1+query("dex", me)*10+
        me->query_skill("martial-cognize", 1);
        dp=target->query_skill("parry")+query("dex", target)*20+
        target->query_skill("martial-cognize", 1);

        me->start_busy(2);
        addn("neili", -400, me);

        if (ap / 2 + random(ap) < dp)
        {
            msg += HIG "然而$n" HIG "抵挡得法，将$N" HIG
            "的攻势一一化解。\n" NOR;
        } else
        {
            addn("neili", -260, me);
            damage = ap * 1 + random(ap * 1 / 5) - 60 - random(40);
            msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
              HIY "$n" BLU "只觉得已经跌入了万劫魔域之中，"HIY"$N"
              WHT "如同地狱幽灵一样手舞足蹈，从九九八十一个方位杀了过去！\n" NOR);
        }

        message_combatd(msg, me, target);

    }
    if(!me->is_fighting(target)) me->fight_ob(target);
    if(!target->is_fighting(me)) target->fight_ob(me);
    remove_call_out("checking");
    call_out("checking", 1, me);
    return 1;
}
*/
