// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <armor.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "蛤蟆扑击"; }

//void tie_result(object me, object target);
void tie_hit(object me, object target);
void pu_hit(object me, object target);

int perform(object me, object target)
{
        object armor,weapon;
        int damage;
        string *limb, type, result, str;

        type = "内伤";

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("你不在战斗中。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你手持兵器，无法施展蛤蟆功的掌法绝技。\n");

        if( (int)me->query_skill("hamagong", 1) < 220 )
                return notify_fail("你的蛤蟆功修为不够。\n");

        if ( me->query_skill_mapped("force") != "hamagong")
                return notify_fail("你现在运使的内功并非蛤蟆功！\n");

        if (me->query_skill_mapped("strike") != "hamagong")
                return notify_fail("你没有准备蛤蟆功，不能使用「蛤蟆扑击」！\n");

        if( query("neili", me) <= 1000 )
                return notify_fail("你的内力不够！\n");

        if( query("jingli", me) <= 500 )
                return notify_fail("你的精力不够！\n");

        delete_temp("puji_time", me);
        remove_call_out("pu_hit");
        pu_hit(me, target);

        return 1;
}

void pu_hit(object me, object target)
{
        object armor;
        int damage, time, ap, dp, pp, fap, hmg, force;
        string msg, *limb, type, result, str;
        object weapon;
        int qi;

        if( !target ) return;

        if( !me || !me->is_fighting(target) ) return;

        if( !living(me) || me->is_ghost() ) return;

        if( !target || environment(me) != environment(target)
                || !me->is_fighting() )
                return;

        if( me->query_skill_mapped("force") != "hamagong" ||
                me->query_skill_mapped("strike") != "hamagong")
                return;

        type = "内伤";

        hmg = (int)me->query_skill("hamagong", 1);
        force = (int)me->query_skill("force", 1);

        ap = attack_power(me, "strike");
        ap = ap*(1+time);

        dp = defense_power(target, "dodge");

        pp = defense_power(target, "parry");

        addn_temp("puji_time", 1, me);
        time=query_temp("puji_time", me);

        if( time == 1 ) msg = HIB "\n$N双腿一弯，蹲下身来，“阁”的一声大叫，运起蛤蟆功劲力，双掌齐发，向前推出。这一推实乃$P毕生功力之所聚，$n猛然感受到山洪海啸般的劲力袭来。\n" NOR;
        else if( time == 2 ) msg = HIM "\n$N第一推刚完，第二推又已迅速异常的赶到，前劲未衰，后劲继至，掌风越发猛烈。\n" NOR;
        else msg = HIR "\n$N眼看前招落空，却毫无慌乱，顺势又是一推，第"+chinese_number(time)+"推的掌风犹如沙漠风暴，一阵猛过一阵，呼啸着向$n扑来。\n"NOR;

        message_combatd(msg , me,target);

        addn("neili", -hmg, me);

        fap = random(ap + dp);

        if( living(target) && fap < dp ) {

                if(time == 1) message_combatd(HIY "$n眼见这一推来势凶猛，挡既不能，避又不可，当下双足一点，跃高四尺，躲开了这一推。\n只听身後腾的一声大响，$N这一推的劲力激起一股狂风巨浪，顿时尘土纷扬，令人惊骇不已。\n\n" NOR, me, target);

                else message_combatd(HIY "$n眼见这一推气势汹汹，当下双足一点，侧跃三尺，又躲开了这一推。\n只听轰的一声巨响，蛤蟆功猛劲激得灰泥弥漫，又是一片尘土飞扬，声势惊人。\n" NOR, me, target);
                if (! target->is_busy())
                target->start_busy(2+random(2));
                me->start_busy(1);
                if( me->query_skill("strike") > time*150 && time < 5)
                        call_out("pu_hit",1,me,target);
        }

        else if( random(ap+pp)<pp && random(5) == 0 && query("race", target) == "人类" )
        {
                weapon=query_temp("weapon", target);
                if(weapon)
                {
                        weapon->unequip();
                        weapon->move(environment(target));
                        target->reset_action();
                        message_combatd(HIR"$N猛觉得劲风罩来，心知不妙，手中"NOR + weapon->name() + HIR"脱手飞出，赶紧也是双掌向前平推。这一下是以硬接硬，刹那之间，两下里竟然凝住不动。\n"NOR, target );
                }
                else message_combatd(HIR"$N猛觉劲风罩来，心知不妙，也是双掌向前平推。这一下是以硬接硬，刹那之间，两下里竟然凝住不动。\n\n"NOR, target );

                message("vision", HIW BLK"两人本是忽纵忽窜、大起大落的搏击，突然间变得两具僵尸相似，连手指也不动一动，似乎气也不喘一口。\n\n"NOR, environment(me), ({ me, target }) );

                addn("neili", -hmg, target);
                if (! target->is_busy())
                target->start_busy(3+random(2));
                me->start_busy(2);
                remove_call_out("tie_hit");
                call_out("tie_hit",2,me,target);
        }

        else {
                if( query_temp("armor/cloth", target) )
                        armor=query_temp("armor/cloth", target);

                if( (!living(target) || (!armor || (armor && query("armor_prop/armor", armor)<150))) && (target->query_skill("dodge")+target->query_skill("parry"))<random((me->query_skill("strike")+me->query_skill("force"))*2/3) && query("race", target) == "人类" )
                {
                        message_vision(HIR"只听$N一声惨叫，这一掌正中小腹。但见$n一个身躯突然平平飞出，腾的一响，尘土飞扬，跌在丈许之外，直挺挺的躺在地下，再也不动。\n\n"NOR, target,target );
                        qi = query("eff_qi", target);
                        if( qi < 1 ) qi = 1;
                        target->receive_wound("qi",qi+1,me);
                        qi = query("qi", target);
                        if( qi < 1 ) qi = 1;
                        target->receive_damage("qi",qi+1,me);
                        addn("neili", -(query("jiali", me)+hmg/2), me);
                        addn("jing", -query("jiajin", me), me);
                }
                else
                {
                        damage=damage_power(me, "force");
                        damage+=query("jiali", me);
                        damage*=3;

                        if(damage < me->query_skill("strike")*time ) damage = me->query_skill("strike")*time;
                        addn("neili", -(query("jiali", me)+hmg/2), me);

                        target->receive_damage("qi", damage,  me);
                        target->receive_wound("qi", random(damage/2)+damage/2, me);
                        if (! target->is_busy())
                        target->start_busy(1+random(3));

                        limb=query("limbs", target);

                        if(random(2) ) type = "瘀伤";
                        result = COMBAT_D->damage_msg(damage, type);
                        result = replace_string( result, "$l", limb[random(sizeof(limb))]);
                        result = replace_string( result, "$p", target->name() );
                        message_combatd(result, me, target);
                }
        }

        me->start_busy(2);
}


void tie_hit(object me, object target)
{
        int sum, n1, n2;
        string msg;

        if( !target || !me || !me->is_fighting(target) ) return;

        if( !living(me) || me->is_ghost() ) return;

        if( !target || environment(me) != environment(target) || !me->is_fighting() ) return;

        sum = me->query_skill("force") + me->query_skill("strike") + target->query_skill("force") + target->query_skill("parry");
        n1=query("neili", me);
        n2=query("neili", target);

        addn("neili", -100*sum/(me->query_skill("force")+me->query_skill("strike")), me);
        if( query("neili", me)<0)set("neili", 0, me);

        addn("neili", -150*sum/(target->query_skill("force")+target->query_skill("strike")+1), target);
        if( query("neili", target)<0)set("neili", 0, target);

        if( n1 > 3000 && n2 > 3000) {
                msg = WHT"此时双方掌力均极强劲，欲分胜负，非使对方重创不可。\n"NOR;

                if( n1 > n2 )
                msg += HIW"二人又僵持一会，$n头顶透出一缕缕的白气，渐渐越来越浓，就如蒸笼一般。\n"NOR;
                else msg += HIW"二人又僵持一会，$N头顶透出一缕缕的白气，渐渐越来越浓，就如蒸笼一般。\n"NOR;
        }

        else {

                if( n1 > n2 ) msg = WHT"$N不断催动蛤蟆功猛劲，毫无衰颓迹象。稍过片刻，$n已是全身大汗淋漓。\n"NOR;
                else msg = WHT"$N脸上黑气大盛，将蛤蟆功发挥到了极致。稍过片刻，$N已是全身大汗淋漓。$n似乎依然中气十足，头顶热气蒸蒸而上。\n"NOR;
                }

        message_combatd(msg , me,target );


        if( query("neili", me)>0 && query("neili", target)>0 && me->is_busy() && target->is_busy() && living(me) && living(target) )
        {
                if (! target->is_busy())
                target->start_busy(3+random(2));
                me->start_busy(2);
                remove_call_out("tie_hit");
                call_out("tie_hit",2, me,target);
                return;
        }

        if( query("neili", target) <= 0 )
        {
                message_vision(HIR "\n$N突然喘不过气来，全身发抖，原来内力已全部耗尽。突闻前胸一片骨裂之声，已被蛤蟆功一掌击中，哼也哼不出一声，仰身向后跌倒，双眼紧闭，脸如白纸，端的是生死难料。\n\n" NOR, target);
                target->receive_wound("qi",query("max_qi", target),me);
                target->receive_damage("qi",query("max_qi", target)+1,me);
                return;
        }

        if( query("neili", me) <= 0 )
        {
                message_vision(HIR "\n$N脸上黑气大作，突然喘不过气来，全身发抖，原来内力已全部耗尽。蛤蟆功立时全部反弹回来，但闻前胸一片骨裂之声，哼也哼不出一声，俯身跌倒，双眼紧闭，脸如黑墨，端的是生死难料。\n\n" NOR, me);
                me->receive_wound("qi",query("eff_qi", me),target);
                me->receive_damage("qi",query("eff_qi", me)+1,target);
        }

//        remove_call_out("tie_result");
//        call_out("tie_result",1,me,target);
}
