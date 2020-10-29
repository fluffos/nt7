// This program is a part of NT MudLIB
// jiutian.c  凤舞九天

#include <ansi.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "凤舞九天"; }

void remove_effect(object me, object target, int dodge, int damage, int parry);

int perform(object me, object target)
{
        object weapon, weapon1 ;
        string msg;
        int extra, dodge, speed, parry ,damage;

        if (!target) target = offensive_target(me);

        if (me->query_skill_mapped("force") != "kurong-changong" &&
            me->query_skill_mapped("force") != "duanshi-xinfa")
                return notify_fail(HIW"你所用得内功心法不对，无法跃起身形。\n" NOR);

        if (!target
        ||      !target->is_character()
        ||      !me->is_fighting(target))
                return notify_fail( HIW "「凤舞九天」只能在战斗中使用。\n" NOR);

        if( query_temp("jiutian", me) )
                return notify_fail( HIW "你正在舞「凤舞九天」！\n" NOR);

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query_skill("kurong-changong", 1) < 130 &&
            (int)me->query_skill("duanshi-xinfa",1) < 130)
                return notify_fail( HIW "你的内功修为未到，无法施展「凤舞九天」。\n" NOR);

        if ((int)me->query_skill("feifeng-whip", 1) < 150)
                return notify_fail( HIW "你的飞凤鞭法修为还不够，尚未领悟到「凤舞九天」。\n" NOR);

        if( query("max_neili", me) <= 1000 )
                return notify_fail( HIW "你的内力修为不足，劲力不足以施展「凤舞九天」！\n" NOR);

        if( query("neili", me)<500 )
                return notify_fail( HIW "你现在内力不够，劲力不足以施展「凤舞九天」！\n" NOR);

        if( query("jingli", me) <= 300 )
                return notify_fail( HIW "你的精力不足，无法施展「凤舞九天」！\n" NOR);

        if( query("gender", me) != "女性" )
                return notify_fail( HIW "「凤舞九天」只有女性能舞！\n" NOR);

        if (! living(target))
                return notify_fail( HIW "对方都已经这样了，还舞给谁看啊！\n" NOR);

        message_vision(MAG"$N向后纵身一跃，翩翩起舞，手中的"NOR+weapon->name()+NOR+MAG"响起阵阵凤鸣，舞姿奇诡莫测，变化无端，宛如凤凰一般刹是好看。\n\n" NOR, me);

        if( random(query("per", me))+8>20 )
        {
                message_vision(HIR"突然$n一个失神，被$N的动作所吸引，顿感心旷神怡，心猿意马，被$N的舞姿迷的神魂颠倒！\n\n"NOR, me, target);
                target->start_busy(random(5)+5);

                if( query_temp("weapon", target)){
                        weapon1=query_temp("weapon", target);
                        if( query("combat_exp", me)<random(query("combat_exp", target)*8/5)){
                                message_vision(HIW"$n手指一松，"NOR+weapon1->name()+NOR HIW"险些脱手！\n" NOR, me, target);
                        }
                        else {
                                message_vision(HIW"$n手上一松，不由自主的丢下了"NOR+weapon1->name()+NOR HIW"！\n" NOR, me, target);
                                weapon1->unequip();
                                weapon1->move(environment(target));
                                target->reset_action();
                        }
                }
                extra = (int)me->query_skill("feifeng-whip",1);
                dodge = extra*3/4 + random(extra/2);
                damage = extra/3 + random(extra/2);
                parry = extra*3/4 + random(extra/5);

                addn_temp("apply/dodge", dodge, me);
                addn_temp("apply/damage", damage, me);
                addn_temp("apply/parry", -parry, target);

                set_temp("jiutian", 25+extra/6, me);
                call_out("checking", 1, me, target, weapon, dodge, damage, parry);

                me->start_busy(1+random(2));
                addn("neili", -250, me);
                addn("jing", -50, me);
        }
        else
        {
                message_vision(RED"就看$n收敛心神，心如明镜，全神贯注，并未被$N的舞姿所迷。\n"NOR, me, target);
                me->start_busy(random(5)+2);
        }
        return 1;
}

void checking(object me, object target, object weapon, int dodge, int damage, int parry)
{
        if (!living(me) || me->is_ghost())
        {
                remove_effect(me, target, dodge, damage, parry);
                return ;
        }
        if( query_temp("jiutian", me)){
        if( !me->is_fighting() )
        {
                message_vision(HIY"\n$N向后一跳，收起了步伐。\n"NOR, me);
                remove_effect(me, target, dodge, damage, parry);
                tell_object(me, HIM"\n你身形一止，速度慢了下来。\n\n"NOR);
                return;
        }
        else if( environment(weapon) != me || weapon != query_temp("weapon", me) )
        {
                message_vision(HIY"\n$N脚步一顿，停止了舞蹈。\n"NOR, me);
                remove_effect(me, target, dodge, damage, parry);
                tell_object(me, HIM"\n你感觉到气血不顺，速度渐渐慢了下来。\n\n"NOR);
                return;
        }
        else if( query("weapon_prop", weapon) == 0 )
        {
                message_vision(HIY"\n$N手中的"NOR+weapon->name()+NOR HIY"已毁，不得不停下脚步。\n"NOR, me);
                remove_effect(me, target, dodge, damage, parry);
                return;
        }
        else if (me->query_skill_mapped("force") != "kurong-changong")
        {
                remove_effect(me, target, dodge, damage, parry);
                tell_object(me, HIY"\n你感到内息不畅，不得不停下脚步。\n\n" NOR);
                return;
        }
        if (random(5) == 1)
                message_vision(HIG"$N身姿如同九天凤凰，潇洒飘逸又威势逼人！\n"NOR,me);
                addn_temp("jiutian", -1, me);
                call_out("checking", 1, me, target, weapon, dodge,damage, parry);
        }
        else {
                remove_effect(me, target, dodge, damage, parry);
                tell_object(me, HIM"\n你感觉到气血不顺，速度渐渐慢了下来。\n\n"NOR);
        }
}

void remove_effect(object me, object target, int dodge, int damage, int parry)
{
        if (!me) return;
        delete_temp("jiutian", me);
        addn_temp("apply/dodge", -dodge, me);
        addn_temp("apply/damage", -damage, me);
        if (!target) return;
        addn_temp("apply/parry", parry, target);
}
