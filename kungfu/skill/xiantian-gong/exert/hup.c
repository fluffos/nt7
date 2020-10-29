// This program is a part of NITAN MudLIB
// hup.c 五气朝元

#include <ansi.h>

#define HUP "「" HIR "五气朝元" NOR "」"

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill,time;
        string msg;
        mapping my;
        int rp;
        int neili_cost;

        if( userp(me) && !query("can_perform/xiantian-gong/hup", me) )
                return notify_fail("你未得高人指点，不知该如何施展" HUP "。\n"); 

        if ((int)me->query_skill("xiantian-gong", 1) < 200)
                return notify_fail("你先天功不够深厚，难以施展" HUP "。\n");
        
        if( (time = time()-query_temp("xtg_hup", me))< 300)
                return notify_fail(RED"你现在气血翻腾，还需要"+(300-time)+"秒才能施展" HUP "。\n"NOR);

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不足，难以施展" HUP "。\n");

        if( query("neili", me)< query("max_neili", me) / 2)
                return notify_fail("你现在的真气不够，难以施展" HUP "。\n");

        my = me->query_entire_dbase();
        if ((rp = (my["max_qi"] - my["eff_qi"])) < 1)
                return (SKILL_D("force") + "/recover")->exert(me, target);

//        if (rp >= my["max_qi"] / 10)
//                rp = my["max_qi"] / 10;

//        skill = me->query_skill("force");
        msg = HIW "$N" HIW "缓缓吐出一口气，顿时气脉通畅，脸色渐渐的变"
              "得平和。\n" NOR;
        message_combatd(msg, me);

        neili_cost = query("max_neili", me) / 2;

        me->receive_curing("qi", rp);
        me->receive_healing("qi", rp * 3 / 2);
        set_temp("xtg_hup",time(),me);
        addn("neili", -neili_cost, me);
        if(query("neili", me) < 0)
        set("neili",0,me);
        me->start_busy(3);
        return 1;
}

