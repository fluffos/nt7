#include <ansi.h>
#include <combat.h>

#define XIAN "「" HIR "阿鼻道三刀" NOR "」"

inherit F_SSERVER;

string attack1(object me, object target, int damage);
string attack2(object me, object target, int damage);

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp;

        if( userp(me) && !query("can_perform/badao/san", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");
                
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAN "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对！\n");

        if ((int)me->query_skill("badao", 1) < 1000)
                return notify_fail("你霸刀火候不足，无法施展" XIAN "。\n");

        if ((int)me->query_skill("force", 1) < 800)
                return notify_fail("你基本内功修为不够，无法施展" XIAN "。\n");

        if( query("neili", me)<3000 )
                return notify_fail("你现在真气不够，无法施展" XIAN "！\n");

        if (me->query_skill_mapped("blade") != "badao")
                return notify_fail("你没有激发霸刀，无法使用" XIAN "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        addn("neili", -3000, me);

        ap=me->query_skill("blade")+me->query_skill("force")+me->query_skill("martial-cognize",1)+query("str", me);
        dp = target->query_skill("dodge") + target->query_skill("force") + target->query_skill("martial-cognize", 1);

        message_combatd(HIW "\n$N" HIW "一声长叹，似乎看尽凡尘沧桑，事态万千，持刀而立，遥望天际 ……\n\n", me, target);        

        // 第一刀
        msg = HIY "$N" HIY "踏步向前，施展出阿鼻道三刀之「一刀入魔」，" + weapon->name() + HIY 
              "顺势劈过，狂风骤起，大地回归黑暗 ……\n" NOR;

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap * 2 + random(ap);
                msg+=COMBAT_D->do_damage(me,target,WEAPON_ATTACK,damage,300+query("str", me),
                                           HIR "$n" HIR "惊魂未定，竟然不知躲避，被$N"
                                           HIR "一刀劈过，刀气如体，口吐鲜血，接连后退。\n" NOR);                
        }
        else
        {
                msg += CYN "$n" CYN "飞身一跃，滚在一边。\n" NOR;
        }

        // 第二刀
        msg += HIY "\n$N" HIY "轻叹，猛然间，手臂一挥，一式阿鼻道三刀之「人间炼狱」已然使出，" + weapon->name() + HIY "长鸣一声"
               "，划破黑暗，吹吸间，一道炽热的白光卷向$n" HIY "，周围空气令人窒息。\n" NOR;

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap * 3 + random(ap);
                msg+=COMBAT_D->do_damage(me,target,WEAPON_ATTACK,damage,300+query("str", me),
                                          (: attack1, me, target, damage :));
        }
        else
        {
                msg += CYN "$n" CYN "胡乱施展招式，竟将这招化解。\n" NOR;
        }

        // 第三刀
        msg += HIY "\n$N" HIY "双眼一红，力量大增，猛然怒呵一声，飞天而起，但见天地又重归黑暗，似乎整个尘世已经"
              "坠入无间地狱般，令人再无半点生念，突然，四周充斥着鬼哭狼嚎的巨响，$N" HIY "却早已没了踪影。\n" NOR;
        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap * 4 + random(ap);
                msg+=COMBAT_D->do_damage(me,target,WEAPON_ATTACK,damage,350+query("str", me),
                                           (: attack2, me, target, damage :));
                                                           

        }
        else
        {
                msg += CYN "$n" CYN "收摄心神，小心应对，竟将此招化解与无形。\n" NOR;
        }

        me->start_busy(4 + random(4));
        message_combatd(sort_msg(msg), me, target);
        return 1;
}

string attack1(object me, object target, int damage)
{
        string msg;

        msg = HIR "$n" HIR "只觉心中一阵凄凉，胸口却已翻腾不息，说不出的难受。\n" NOR;

        addn("neili", -1*damage/2, target);
        
        return msg;
}

string attack2(object me, object target, int damage)
{
        string msg;

        msg = HIR "$n" HIR "早已十魂失了八魄，正惊疑间，眼前一闪，刀气透体而过。\n" NOR;

        target->receive_wound("jing", damage / 8, me);
        if (random(4) == 1)target->start_busy(5 + random(5));
        
        return msg;        
}