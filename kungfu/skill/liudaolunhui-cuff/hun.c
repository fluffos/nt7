// hun.c 无间轮回

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("liudaolunhui-cuff", 1);

        if (! me->is_fighting(target))
                return notify_fail("无间轮回只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("cuff") != "liudaolunhui-cuff") 
                return notify_fail("你没有用六道轮回拳法，无法使用无间轮回绝招！\n");

        if( me->query_skill_prepared("cuff") != "liudaolunhui-cuff" ) 
                return notify_fail("你所备的并非六道轮回拳法，不能使用无间轮回绝招！\n"); 

        if (skill < 100)
                return notify_fail("你的六道轮回拳法等级不够，练好了再来！\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你拿着武器如何使用拳法绝招？\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够。\n");
        
        ap = me->query_skill("cuff") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIY "$N" HIY "左手斜指天际，右手沉掌向地，嘴中低沉吟唱：『天上地下，惟我独尊』\n" 
              "$n" HIY "只觉一股浑厚的劲气旋绕而来，顿时胸口郁闷，口鼻难于呼吸。\n\n" NOR;

        msg += HIY "$N" HIY "突然腾身而起，身形幻化出众生相，翻滚沉浮，如地狱魔煞扑向$n" HIY "，闪电般发出数招。\n\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        msg = HIW "\n在$n" HIW "踉跄后退时，$N" HIW "口中轻诵『" HIC "天" HIW "、" HIG "人" HIW  "、" HIB "阿修罗" HIW "、" HIY "畜牲" HIW "、" HIM "饿鬼" HIW "、" HIR "地狱" HIW "』"
              HIW "\n每念一字便有重重" NOR BLU "鬼影" HIW "闪现，待到念完，无数鬼影遁入往生轮回。\n\n"NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIR "$n" HIR "心胆俱裂，迷惘失神下已被无数鬼魂纠缠，浑身血柱四射！\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIW "$n" HIW "闭目静神，凭借思感左右闪避，终于躲过这惊怖一击。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
        addn("neili", -damage/3, me);
        return 1;
}

