// qixing. 七星绝命剑

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon=query_temp("weapon", me);
        int damage;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("七星绝命剑只能对战斗中的对手使用。\n");

    if( (int)me->query_skill("quanzhen-jianfa", 1) < 90 )
                return notify_fail("你的全真剑法不够熟练，使不出七星绝命剑。\n");
  
    if( !weapon || query("skill_type", weapon) != "sword"
        || me->query_skill_mapped("sword") != "quanzhen-jianfa")
                return notify_fail("你现在无法使用七星绝命剑。\n");

    if( query("neili", me)<200 )
                return notify_fail("你的内力不够，无法使用七星绝命剑。\n");

         msg = MAG "$N一声长啸，一抖手中剑，顿时形成一道剑幕，狂风暴雨般压向$n。就在
$n慌乱之间，剑幕中飞出七朵寒星，如流星般射向$n。\n";

        if( random(query("combat_exp", me))>query("combat_exp", target)/3){
                msg += "$n躲闪不及，已然中剑！\n";
                damage = 3*(int)me->query_skill("quanzhen-jianfa", 1);
                damage = damage / 2 + random(damage / 2);
                if( damage>query("neili", target)/10 )
                        damage-=query("neili", target)/15;
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/3);
                 if( damage < 40 ) msg += HIY"$n已身中数剑，身上到处是血。\n"NOR;
                 else if( damage < 80 ) msg += HIR"$n身中七剑，鲜血狂喷而出！\n"NOR;
                 else msg += RED"$n“哇”的狂叫一声，身上喷出七道血剑！\n"NOR;
                message_vision(msg, me, target);
        } 
        else {
                 msg += HIW"$n情急之中向后激飞，随机趴下，堪堪躲过了这致命一击。\n" NOR;
                message_vision(msg, me, target);
        }
        addn("neili", -180, me);
        me->start_busy(2);

        return 1;
}
