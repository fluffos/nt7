// This program is a part of NT MudLIB

#include <ansi.h>

inherit F_SSERVER;

string name() { return "发射暗器"; }

void remove_shoot(object);

int perform(object me, object target)
{
        int t=query_temp("baituo/shoot", me);
        string type, *limbs, str, dodge_skill, limb, result;
        object weapon;
        int poi_amount, level, exp1, exp2;

        if( query("no_fight", environment(me)) )
                return notify_fail("这里不能发射暗器。\n");

        if( !target && me->is_fighting()) target = offensive_target(me);

        if (!target || !target->is_character())
                return notify_fail("你要对谁发射暗器？\n");

        if( target == me )
                return notify_fail("对自己发射暗器？\n");

        if( t && (time()-t) < 10 )
                return notify_fail("你刚刚才发射了暗器，短时间内不宜故技重施！\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                 return notify_fail("你必需手持能发射暗器的蛇杖。\n");

        type=query("snake_type", weapon);

        if( !type && query("id", weapon) != "shezhang" )
                return notify_fail("你的"+weapon->name()+"上并没有暗器机关。\n");

        level = (int)me->query_skill("lingshe-zhangfa", 1);
        if (level < 40 )
                return notify_fail("你的灵蛇杖法不够娴熟，无法操纵发射暗器的机关。\n");

        if ((int)me->query_skill("poison", 1) < 40 )
                return notify_fail("你的基本毒技造诣太浅，无法操纵发射暗器的机关。\n");

        if(( me->query_skill_mapped("force") != "hamagong") && ( me->query_skill_mapped("force") != "jiuyin-hamagong"))
                return notify_fail("你所用的内功与「灵蛇杖法」气路相悖！\n");

        limbs=query("limbs", target);
        //level = level/2;
        poi_amount = level + me->query_skill("poison", 1);

        if( query("neili", me)<poi_amount )
                return notify_fail("你的内力不够。\n");
        if( query("jingli", me)<50 )
                return notify_fail("你的精力不够。\n");

        exp1=query("combat_exp", me);
        exp2=query("combat_exp", target);

        if(exp1*3<exp2 && exp2> 1000000)
                return notify_fail("你料知"+target->name()+"这等身手，杖头暗器也奈何他不得，不如不发，免惹耻笑。\n");

        message_combatd(HIB"$N将"+weapon->name()+HIB"在地下一顿，呜的一声怪响，杖头中飞出一件奇形暗器，笔直往$n射去。\n"NOR, me, target);

        addn("neili", -poi_amount/2, me);
        addn("jingli", -50, me);

        if( query("neili", me)>random(query("neili", target)) && (exp1/100)>random(exp2/100)){

                message_combatd(HIR"那暗器去得好快，祗听$n一声惨嚎，尚未看清暗器来路，已被射中"+(arrayp(limbs)?limbs[random(sizeof(limbs))]:"身体")+"！\n"NOR, me, target);

                if( type == "怪蛇" || type == "灵蛇" )
                     target->apply_condition("snake_poison",
                        poi_amount*3 + target->query_condition("snake_poison"));
                else
                     target->apply_condition("snake_poison",
                        poi_amount*3 + target->query_condition("snake_poison"));
                set("poisoner", me, target);
                target->receive_wound("qi", random(level) + level/2 , me);
                target->start_busy(random(2));
                result=COMBAT_D->eff_status_msg(query("qi", target)*100/query("max_qi", target));
                message_combatd("( $N"+result+" )\n", target);

        }
        else {
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                str = SKILL_D(dodge_skill)->query_dodge_msg(limb);
                message_vision(str, me, target);
        }

        target->kill_ob(me);
        set_temp("baituo/shoot", time(), me);
        call_out("remove_shoot", 5, me);
        me->start_busy(random(2));

        return 1;
}

void remove_shoot(object me)
{
        if( !me || !query_temp("baituo/shoot", me))return ;

        delete_temp("baituo/shoot", me);
        tell_object(me, "你的蛇杖里的暗器准备好了。\n");
}
