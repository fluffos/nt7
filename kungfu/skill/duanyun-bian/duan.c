#include <ansi.h>

inherit F_SSERVER;

int second_hit(object me, object target);
int duo(object me, object target);
int duo2(object me, object target);

string name() { return "断云助日"; }

int perform(object me, object target)
{
        object weapon;
        mapping myfam;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「断云助日」只能对战斗中的对手使用。\n");

         /*
        if( (int)me->query_skill("xiantian-gong",1) < 150 )
                return notify_fail("你先天功修为不足！\n");
         */

        if( (int)me->query_skill("taoism",1) < 150 )
                return notify_fail("你道学修为修为不足！\n");

        if( me->query_skill("duanyun-bian",1) < 150 )
                return notify_fail("你的「断云鞭法」修为不足！\n");

        if( me->query_skill("whip",1) < 150 )
                return notify_fail("你的鞭法的基本功不扎实！\n");

        if( me->query_con() < 40 )
                return notify_fail("你的根骨太差！\n");

        if( query("neili", me) <= 300 )
                return notify_fail("你的内力不够使用「断云助日」！\n");

        if( !query_temp("weapon", me) || query("skill_type", query_temp("weapon", me)) != "whip" )
                return notify_fail("你并没有装备鞭作为武器。\n");

        /*
        if( query("combat_exp", me)/100>query("shen", me) )
                return notify_fail("你的侠义正气太低，无法控住心中的邪念，使此招无益有损。\n");
        */

        if( query_temp("duanyun", me) )
                return notify_fail("你正在使用「断云助日」绝招。\n");

        message_combatd(HIW"\n$N心中平和，渐渐将断云鞭法使得圆转如意，手中"+(query("name", query_temp("weapon", me)))+HIW"在内力摧动下闪出点点银光，有如云彩将$n逐渐包围在其中。\n\n"NOR,me,target);

        set_temp("duanyun", 1, me);

        addn("neili", -me->query_skill("whip")/2, me);

        call_out("second_hit", 1, me, target);

        return 1;
}

int second_hit(object me, object target){

        int ap, dp, damage;
        string str;

        if (!me) return 0;

        if( !target || !me->is_fighting(target) )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !living(me) || me->is_ghost() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !target || environment(me) != environment(target) || !me->is_fighting() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if (!query_temp("weapon",me) || query("skill_type", query_temp("weapon",me)) != "whip")
        {
                delete_temp("duanyun", me);
                message_combatd (HIY"\n$N已手中无鞭，无法将绝招继续，只得运功收招。\n"NOR,me);
                return 1;
        }

        if(me->is_fighting()){

                message_vision(HIY"\n$N内力鼓荡，一声清啸声中，向$n猛地发出三招，瞬时间鞭上银光陡散，风声大作。\n"NOR, me, target);

                addn("jiali", me->query_skill("whip",1)/5, me);
                addn_temp("apply/attack", me->query_skill("whip",1), me);
                addn_temp("apply/damage", me->query_skill("whip",1), me);

                COMBAT_D->do_attack(me,target,query_temp("weapon", me));

                COMBAT_D->do_attack(me,target,query_temp("weapon", me));

                addn("jiali", -me->query_skill("whip",1)/5, me);
                addn_temp("apply/attack", -me->query_skill("whip",1), me);
                addn_temp("apply/damage", -me->query_skill("whip",1), me);

                ap=query("combat_exp")/100+me->query_skill("whip", me)+query("neili", me);
                if (living(target))
                      dp=query("combat_exp")/100+target->query_skill("whip", target)+query("neili", target);
                else  dp = 1;
                message_combatd(HIY"\n两招过后，$N招数一变，手中"+query("name", query_temp("weapon", me))+HIY"在空中划了一个弧线，向$n击落。\n"NOR,me,target);

                if(random(ap)>dp/2){

                        message_combatd(HIR"\n只听见$n一声惨叫，"+query("name", query_temp("weapon", me))+HIR"已经打在$n肩头，鲜血溅了一地。\n\n"NOR,me,target);

                        damage=me->query_skill("duanyun-bian",1)*(random(6)+3);

                        if (damage<500) damage=500;
                                if (damage>2000) damage=2000;

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage/2,me);

                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                        message_combatd("($N"+str+")\n", target);

                } else if(random(ap)>dp/3 && objectp(query_temp("weapon",target)) && me->is_fighting() && random(4)==1){

                        message_combatd(HIG"\n$n见敌人招势凶猛，忙举起手中"+query("name", query_temp("weapon", target))+HIG"招架。\n",me,target);
                        message_combatd(HIW"\n$N鞭梢微扬，已经将$n手中的"+query("name", query_temp("weapon", target))+HIW"卷住，两人同时运力回夺。\n"NOR,me,target);

                        me->start_busy(3);
                        target->start_busy(3);

                        call_out("duo", 3, me, target);

                        return 1;

                } else if(random(ap)>dp/3 && !objectp(query_temp("weapon",target)) && me->is_fighting() && random(4)==1){

                        message_combatd(HIG"\n$n身随意转，微微一晃已经将鞭梢抓住，两人同时运力回夺。\n"NOR,me,target);

                        me->start_busy(4);
                        target->start_busy(4);

                        call_out("duo2", 3, me, target);

                        return 1;

                } else if(random(ap)>random(dp)) {

                        message_combatd(HIY"\n$n见此招来势凶猛，大骇之下向后跳开。\n"NOR, me, target);

                        message_combatd(HIG"\n$N一击不中，身子一转，反手又是一招，猛地向$n打去。\n"NOR,me,target);

                        addn_temp("apply/attack", me->query_skill("whip",1), me);
                        addn_temp("apply/damage", me->query_skill("whip",1), me);

                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

                        addn_temp("apply/attack", -me->query_skill("whip",1), me);
                        addn_temp("apply/damage", -me->query_skill("whip",1), me);

                } else
                        message_combatd(HIY "\n$n见此招来势凶猛，忙向后跃开。\n"NOR,me,target);

                me->start_busy(2+random(2));
        } else
                message_combatd(HIY "\n$N见战势已必，长长的吸了一口气，将内力收回。\n"NOR, me);

        delete_temp("duanyun", me);
        return 1;
}

int duo(object me, object target)
{
        int amount1, amount2;

        if (!me) return 0;

        if( !target || !me->is_fighting(target) )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !living(me) || me->is_ghost() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !target || environment(me) != environment(target) || !me->is_fighting() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if (!query_temp("weapon",me) || query("skill_type", query_temp("weapon", me)) != "whip")
        {
                delete_temp("duanyun", me);
                message_combatd (HIY"\n$N已手中无鞭，无法将绝招继续，只得运功收招。\n"NOR,me);
                return 1;
        }

        if( (query("neili", me)<(me->query_skill("force",1)*15) || query("neili", target)<(target->query_skill("force",1)*15))){

                if( query("neili", me)>query("neili", target)){

                        message_combatd(HIG"\n$N运足了气力，猛地将"+query("name", query_temp("weapon", me))+HIG"向后一拉，将$n手中的"+query("name", query_temp("weapon", target))+HIG"拉得脱手而出，掉在了地上。\n"NOR,me,target);

                        message_combatd(HIG"\n$N顺手就是一招，向$n击去。"NOR,me,target);

                        addn("jiali", me->query_skill("whip",1), me);
                        addn_temp("apply/attack", me->query_skill("whip",1), me);
                        addn_temp("apply/damage", me->query_skill("whip",1), me);

                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

                        addn("jiali", -me->query_skill("whip",1), me);
                        addn_temp("apply/attack", -me->query_skill("whip",1), me);
                        addn_temp("apply/damage", -me->query_skill("whip",1), me);

                        query_temp("weapon", target)->move(environment(me));

                        target->start_busy(2+random(3));
                } else {

                        message_combatd(HIG"\n$n运足了气力，猛地将"+query_temp("weapon",query("name",  target))+HIG"向后一拉，将$N手中的"+query("name", query_temp("weapon", me))+HIG"拉得脱手而出，掉在了地上。\n"NOR,me,target);

                        query_temp("weapon", me)->move(environment(me));

                        me->start_busy(2+random(3));
                }

        } else {

                message_combatd(WHT"\n只见$N和$n运足了内力用力回夺自己的兵刃，两人的衣服在内力鼓荡下如遇骤风。\n"NOR, me, target);

                amount1=me->query_skill("force",1);
                amount2=target->query_skill("force",1);

                if(random(amount1)>random(amount2)){
                        message_combatd(YEL"\n只见$n身子一晃，似乎有些支持不住。\n"NOR, me, target);
                        addn("neili", -amount1, target);
                } else {

                        message_combatd(YEL"\n只见$N身子一晃，似乎有些支持不住。\n"NOR, me, target);
                        addn("neili", -amount2, me);
                }
                addn("neili", -100, me);
                addn("neili", -100, target);

                me->start_busy(4);
                target->start_busy(4);

                call_out("duo", 3, me, target);

                return 1;
        }
        delete_temp("duanyun", me);
        return 1;
}

int duo2(object me, object target){

        int amount1, amount2;

        if (!me) return 0;

        if( !target || !me->is_fighting(target) )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !living(me) || me->is_ghost() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !target || environment(me) != environment(target) || !me->is_fighting() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if (!query_temp("weapon",me) || query("skill_type", query_temp("weapon", me)) != "whip")
        {
                delete_temp("duanyun", me);
                message_combatd (HIY"\n$N已手中无鞭，无法将绝招继续，只得运功收招。\n"NOR,me);
                return 1;
        }

        if( (query("neili", me)<(me->query_skill("force",1)*15) || query("neili", target)<(target->query_skill("force",1)*15))){

                if( query("neili", me)>query("neili", target)){

                        message_combatd(HIG"\n$N运足了气力，猛地将"+query("name", query_temp("weapon", me))+HIG"夺回，顺手就是一招，向$n击去。"NOR,me,target);

                        addn("jiali", me->query_skill("whip",1), me);
                        addn_temp("apply/attack", me->query_skill("whip",1), me);
                        addn_temp("apply/damage", me->query_skill("whip",1), me);

                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));


                        addn("jiali", -me->query_skill("whip",1), me);
                        addn_temp("apply/attack", -me->query_skill("whip",1), me);
                        addn_temp("apply/damage", -me->query_skill("whip",1), me);

                        target->start_busy(random(3));

                } else {

                        message_combatd(HIG"\n$n运足了气力，猛地将$N手中的"+query("name", query_temp("weapon", me))+HIG"拉得脱手而出，掉在了地上。\n"NOR,me,target);

                        query_temp("weapon", me)->move(environment(me));

                        me->start_busy(2+random(3));
                }

        } else {

                message_combatd(WHT"\n只见$N和$n运足了内力用力回夺，两人的衣服在内力鼓荡下如遇骤风。\n"NOR, me, target);

                amount1=me->query_skill("force",1);
                amount2=target->query_skill("force",1);

                if(random(amount1)>random(amount2)){
                        message_combatd(YEL"\n只见$n身子一晃，似乎有些支持不住。\n"NOR, me, target);
                        addn("neili", -amount1, target);
                } else {

                        message_combatd(YEL"\n只见$N身子一晃，似乎有些支持不住。\n"NOR, me, target);
                        addn("neili", -amount2, me);
                }
                addn("neili", -100, me);
                addn("neili", -100, target);

                me->start_busy(4);
                target->start_busy(4);

                call_out("duo2", 3, me, target);

                return 1;
        }
        delete_temp("duanyun", me);
        return 1;
}
