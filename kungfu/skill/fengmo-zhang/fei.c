// lianhuan.c  疯魔杖法之疯魔飞杖

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "疯魔飞杖"; }
void check_fight(object me, object target, object weapon);
private int remove_attack(object me, object weapon);

int perform(object me, object target)
{
        object weapon;
        int skill;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("疯魔飞杖只能对战斗中的对手使用。\n");

        if( query_temp("fengmo", me) )
                return notify_fail("你已在使用疯魔飞杖了！\n");

        weapon=query_temp("weapon", me);
        if( !objectp(weapon) || query("skill_type", weapon) != "staff" )
                return notify_fail("你手中无杖，如何能够施展疯魔飞杖？\n");

        if( me->query_skill_mapped("force") != "huntian-qigong" )
                return notify_fail("你所用的并非混天气功，无法配合杖法施展疯魔飞杖！\n");

        if( me->query_skill("force") < 100 )
                return notify_fail("你的混天气功火候未到，无法配合杖法施展疯魔飞杖！\n");

        if( me->query_skill("staff") < 100 )
                return notify_fail("你疯魔杖法修为不足，还不会使用疯魔飞杖！\n");

        if( query("neili", me) <= 300 )
                return notify_fail("你的内力不够施展疯魔飞杖！\n");
        if( query("jingli", me) <= 200 )
                return notify_fail("你的精力不够施展疯魔飞杖！\n");

        skill = me->query_skill("staff");

        message_combatd(HIR "\n$N大喝一声将手中急转着的"+weapon->name()+"脱手掷出，在空中高低左右回旋！\n\n" NOR,
                        me, target);

        set_temp("fengmo", 1, me);
        set_temp("location", file_name(environment(me)), me);
        addn("neili", -200, me);
        addn("jingli", -100, me);
        me->start_busy(3);
        weapon->unequip();

        set("no_clean_up", 1, weapon);
        me->reset_action();
        call_out("check_fight", 0, me, target, weapon);

        return 1;
}

void check_fight(object me, object target, object weapon)
{
        string msg;
        int damage;

        if ( !objectp( me ) ) return;
                me->reset_action();

        if( query_temp("fengmo", me) >= me->query_skill("fengmo-zhang",1)/100 )
        {
                call_out("remove_attack", 1, me, weapon);
        }
        else if( me->is_fighting() && query_temp("fengmo", me) )
        {

                msg = HIM "\n突然间" + weapon->name() + HIM "自行向$n猛然飞撞过去！\n" NOR;

                if( random(query("level", me))>query("level", target)/2 )
                {
                        damage = damage_power(me, "fengmo-zhang");
                        target->receive_damage("qi", damage, me);
                        msg += HIR "$n只觉一股大力铺天盖地般压来,登时眼前一花，两耳轰鸣,哇的喷出一口鲜血！！\n" NOR;


                } else
                {
                        msg += YEL "$n看得分明，身形一让，避过了" + weapon->name() + YEL "！\n" NOR;
                }
                message_combatd(msg, me, target);
                message_combatd(HIR "\n$N猛吸一口气，飘身赶上$n伸掌在杖尾一推，将其又推在半空飞旋。\n\n" NOR,
                                me, weapon);

                addn_temp("fengmo", 1, me);
                call_out("check_fight", 1, me, target, weapon);
        } else
        {
                call_out("remove_attack", 1, me, weapon);

        }
}

int remove_attack(object me, object weapon)
{
        remove_call_out("check_fight");
        if ( !objectp( me ) ) return 1;
        delete_temp("fengmo", me);

        if( file_name(environment(me)) == query_temp("location", me) && living(me) )
        {
                weapon->move(me);
                set("no_clean_up", 0, weapon);
                weapon->wield();
                message_combatd(YEL "\n$N纵身上前，将飞旋的$n收回。\n\n" NOR, me, weapon);
        } else
        {
                weapon->move(query_temp("location", me));
                message("vision", "只听得锵的一声，"+weapon->name()+"力尽由半空跌落。\n",
                        environment(weapon), ({weapon}) );
        }

        delete_temp("location", me);

        return 1;
}
