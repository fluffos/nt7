// wuguang.c 断云鞭法「日月无光」

#include <ansi.h>

inherit F_SSERVER;

string name() { return "日月无光"; }
int perform(object me, object target)
{
        int damage, power;
        string msg;
        object weapon;
        int ap, dp;

        if( !objectp(target) ) {target = offensive_target(me);}

        if( !target || !target->is_character() || target == me ||
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(name()+"只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "whip" )
                return notify_fail(HIR"装备鞭才能使用「日月无光」？\n"NOR);

        if( me->query_skill("duanyun-bian", 1) < 150 )
                return notify_fail("你的断云鞭法火候不够，使不出"+name()+"。\n");

        if( me->query_skill("whip",1) < 150 )
                return notify_fail("你的鞭法的基本功不扎实！\n");

        if( query("max_neili", me)<600 )
                return notify_fail(RED"你内力修为不足，无法运足内力。\n"NOR);

        if( query("neili", me)<600 )
                return notify_fail(HIC"你现在内力不够，没能将"+name()+"使完！\n"NOR);

        msg=HIC"$N"HIC"一声大喝，右手一振，手中"+query("name", weapon)+HIC"脱手飞出。只见满天鞭影，盘旋缭绕，遮闭天日，劈头盖脑向$n"HIC"砸了下去！\n"NOR;
        ap = attack_power(me, "whip");
        dp = defense_power(target, "force");
        if( ap / 2 + random(ap) > dp )
        {
                if( query("shen", me)>1000000 )
                        power = 1000000;
                else if( query("shen", me)>0 )
                        power=query("shen", me);
                else power = 3000;
                if( query("shen", target)<0 )
                        power=power*2;
                damage = damage_power(me, "whip") + random((int)(power/1000))+(int)(power/3000);
                addn("neili", -600, me);
                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(1+random(3));
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
                target->receive_damage("jing", damage/4,me);
                msg += HIR"$n疾忙返身后跃，但鞭势疾如电闪，但见黑影如压城之势而来，全身如遭"
                       "雷击，一时不知挨了多少鞭，不禁惨声连连！\n"NOR;
        } else
        {
                me->start_busy(2);
                msg += HIY"可是$n"HIY"一纵数丈，一下就跃出了$N的鞭影。\n"NOR;
                addn("neili", -200, me);
        }
        msg+=HIC+query("name", weapon)+HIC+"落下，倒插在地上，犹振然弄威作响。\n"NOR;
        weapon->move(environment(me));
        message_combatd(msg, me, target);

        return 1;
}
