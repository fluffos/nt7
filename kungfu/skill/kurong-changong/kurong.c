
// kurong.c 枯荣心法
// Modify By Scatter

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("枯荣心法对他人毫无作用！\n");

        if( query_temp("kurong", me) )
                return notify_fail("你已在运转枯荣心法了。\n");

        if (me->query_skill("kurong-changong",1) < 100
                || me->query_skill("force",1) < 100
                || me->query_skill("buddhism",1) < 100 )
                return notify_fail("你的尚未参通枯荣禅，强运枯荣心法毫无益处！\n");

        if( query("max_neili", me)<2000
                 || query("neili", me)<query("max_neili", me)/10 )
                return notify_fail("你的内力不够运转枯荣心法！\n");

        skill=me->query_skill("kurong-changong",1)+me->query_skill("buddhism",1);

        message("vision",HIW"\n"+query("name", me)+"双掌合十，气息流转下，一张脸片刻间变得血肉全无只剩枯骨！再片刻，又回复血肉充盈的模样。\n\n"NOR,environment(me),me);
        tell_object(me, HIW "\n你双掌合十，运转枯荣心法，一股真气自丹田而生，沿心脉流转不息，脸上一枯一荣闪现，片刻即回复正常。\n\n" NOR);

        set_temp("kurong", skill*4*query("max_neili", me)/2000, me);

        call_out("checking", 1, me);
        addn("neili", -query("max_neili", me)/10, me);

        return 1;
}

void checking(object me)
{
        int maxqi, amount;
        int delta;

        if (!me) return;

        if (!living(me))
        {
                delete_temp("kurong", me);
                return;
        }

        if( !query_temp("kurong", me)){
                tell_object(me, HIW "你感到丹田真气混浊，运转的枯荣心法渐渐散去。\n" NOR);
                return;
        }

        if (me->query_skill_mapped("force") != "kurong-changong")
        {
                delete_temp("kurong", me);
                return;
        }

        if (!me->is_fighting()) {
                if( query_temp("kurong", me) <= 50 )
                        delete_temp("kurong", me);
                else addn_temp("kurong", -50, me);
        }

        maxqi=query("eff_qi", me);

        if (me->is_ghost()) {
                delete_temp("kurong", me);
                return;
        }

        if( living(me) && (maxqi<query("max_qi", me)*95/100 && query("neili", me)>150)){
                amount=(me->query_skill("kurong-changong",1)+me->query_skill("buddhism",1))/4+query("con", me);
                delta = ABILITY_D->check_ability(me, "full-krcg-kurong"); // 门派ab
                if( delta ) amount += amount*delta/100;
                addn("neili", -100, me);
                me->receive_curing("qi", amount);
                message_vision("$N深深吸了几口气，气息流转下伤口的血流自动止住了。\n", me);
        }

        if( living(me) && (query("qi", me)<(maxqi*2/3))){
                amount=maxqi-query("qi", me);
                delta = ABILITY_D->check_ability(me, "full-krcg-kurong"); // 门派ab
                if( delta ) amount += amount*delta/100;
                if( amount>query_temp("kurong", me))amount=query_temp("kurong", me);
                addn_temp("kurong", -amount, me);
                me->receive_heal("qi", amount);
                message_vision("$N深深吸了几口气，脸色看起来好多了。\n", me);
        }

        call_out("checking", 1, me);
        return;
}
