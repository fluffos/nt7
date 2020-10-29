// wuliang.c 八卦掌「乾坤无量」
// Create for Haiyan 2002

#include <ansi.h>


inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count, acter;
        int i, bsy, lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「乾坤无量」只能对战斗中的对手使用。\n");

        if (me->query_skill_mapped("strike") != "bagua-zhang") 
                return notify_fail("你没有激发八卦掌，无法施展「乾坤无量」。\n"); 

        if ((int)me->query_skill("bagua-zhang", 1) < 120)
                return notify_fail("你的八卦掌不够娴熟，不会使用「乾坤无量」。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("「乾坤无量」只能空手施展。\n");  

        if (! me->query_skill_prepare() || me->query_skill_prepare() && 
            me->query_skill_prepared("strike") != "bagua-zhang") 
                return notify_fail("你现在没有准备使用八卦掌，无法使用「乾坤无量」！\n"); 

        if( query("neili", me)<350 )
                return notify_fail("你的真气不够，无法使用「乾坤无量」。\n");

        msg = HIY "$N" HIY "掌法忽然变快，使出八卦掌法「乾坤无量」，脚下沿八卦方位疾走，双掌虚虚实实地拍向$n。\n" NOR;

        dp = (target->query_skill("force", 1) + 
             target->query_skill("parry", 1) +
             target->query_skill("martial-cognize", 1)) / 3 +
             target->query_skill("count", 1); 

        if( query("character", me) == "光明磊落" || 
            query("character", me) == "国土无双" || 
            query("character", me) == "狡黠多变" )
             acter = 3;
        else
             acter = 4;

        ap = (me->query_skill("taiji-shengong", 1) +
             me->query_skill("bagua-zhang", 1) +
             me->query_skill("martial-cognize", 1) + 
             me->query_skill("taoism", 1)) / acter; 

        if ( ap / 2 + random(ap) > dp )
        {
                msg += HIR "$n" HIR "被$N" HIR
                       "这一变化攻了个措手不及，“嘭嘭嘭”连中数掌，" HIR
                       "喷出几口鲜血，脸色变得煞白！\n" NOR;
                count = ap / 28; 
                bsy = 2;
                lvl = me->query_skill("bagua-zhang", 1) / 60;
                addn_temp("apply/attack", count, me);
        } else
        {
                msg += HIC "$n" HIC "见$N" HIC "忽然变招，不敢大意，连忙屏息凝气，小心应对，将$N"
                       HIC "的招式尽数拆解。\n" NOR;
                count = 0;
                lvl = 0;
                bsy = 5;
        }
                
        message_combatd(msg, me, target);

        addn("neili", -150, me);

        for (i = 0; i < lvl; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(2 + random(bsy));

        return 1;
}