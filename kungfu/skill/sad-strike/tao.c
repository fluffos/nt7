// This program is a part of NT MudLIB

#include <ansi.h>

inherit F_SSERVER;

string name() { return "怒海惊涛"; }

int perform(object me, object target)
{
        object weapon;
        int myexp, targexp, damage, skill, merand, targrand, targneili,time,i;
        string str,*limb,type;
        mapping myfam;
        int tmp_jiali,dmg;
        int num,ap,dp;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「怒海惊涛」只能对战斗中的对手使用。\n");

        if( (!(myfam=query("family", me)) || myfam["family_name"] != "古墓派") )
                  return notify_fail("只有古墓弟子才能用「怒海惊涛」。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("空手才能施展「怒海惊涛」！\n");

        if( me->query_skill_mapped("force") != "surge-force" )
                return notify_fail("你所用内功的并非怒海狂涛，使不出「怒海惊涛」！\n");

        if( (int)me->query_skill("surge-force",1) < 150 )
                return notify_fail("你内功修为太差，不能运用「怒海惊涛」！\n");

        if( me->query_skill("sad-strike",1) < 150 )
                return notify_fail("你黯然销魂掌修为太差，不能运用「怒海惊涛」！\n");

        if( (string)me->query_skill_mapped("unarmed") != "sad-strike")
                return notify_fail("你并没有激发黯然销魂掌作为掌法。\n");

        if( (string)me->query_skill_prepared("unarmed") != "sad-strike")
                return notify_fail("你并没有准备黯然销魂掌。\n");

        if ( !living(target))
               return notify_fail("现在不没必要用「怒海惊涛」吧！\n");

        if( query("neili", me) <= 1000 )
                return notify_fail("你的内力不够使用「怒海惊涛」！\n");

        ap = attack_power(me,"unarmed")+query("jiali", me);
        dp = defense_power(target, "parry") + target->query_skill("force");
        damage = damage_power(me, "unarmed");
        damage+= query("jiali", me);

        skill=me->query_skill("sad-strike",1);

        message_combatd(HIW"\n$N的掌风隐隐带着潮涌之声，掌风鼓荡，竟似有狂潮涌来，这正是神雕大侠当年在海边练出的绝技。 \n\n"NOR,me,target);

        if (ap/2 + random(ap) > dp)
        {
                message_combatd(HIR"$n哪里躲避得开，大惊下已经给$N的掌风印上胸口，一口鲜血狂喷而出！\n\n",me,target);
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2,me);
                if (! target->is_busy())
                        target->start_busy(1);
        } else
        {
                message_combatd(HIY"$n见状不妙，立刻就地一个打滚，虽然姿势难看以及，不过总算避开了$N这一掌。\n\n"NOR,me,target);
        }

        message_combatd(HIW"\n$N在掌风达到顶峰之时，跟着“魂不守舍”、“倒行逆施”、“若有所失”，连出三招。\n\n"NOR,me,target);

        dp = defense_power(target, "dodge") + target->query_skill("force");
        if (ap/2 + random(ap) > dp)
        {
                message_combatd(HIR"$n惊魂未定，正喘气之际，不提防又一阵猛烈的气浪扑面冲来，复遭$N掌风重创！\n\n",me,target);
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2,me);
                if (! target->is_busy())
                        target->start_busy(1);
        } else
        {
                message_combatd(HIY"$n顾不得反击，急身后退三丈，脸颊给$N的掌风扫到，微微发红，不过总算避开了$N这三掌。\n\n"NOR,me,target);
        }

        message_combatd(HIW"跟着$N腾身而起，一招“行尸走肉”，闪电般踢出一脚。\n\n"NOR,me);

        dp = defense_power(target, "force") + target->query_skill("force");
        if (ap/2 + random(ap) > dp)
        {
                message_combatd(HIR"$n眼看着这霸气冲天的一脚，已然放弃了抵抗，整个脸部给$N重重踹上，牙齿皆碎，面目血色狰狞！\n\n",me,target);
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2,me);
                if (! target->is_busy())
                        target->start_busy(1);
        } else
        {
                message_combatd(HIY"$n双足点地，拔天而起，从$N的头顶掠过，脚下劲气呼啸而过，真是险之又险！\n\n"NOR,me,target);
        }

        addn("neili", -600, me);
        me->start_busy(2+random(2));

        return 1;
}

