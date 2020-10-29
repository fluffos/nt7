#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "碧焰滔天" NOR; }
string attack(object me, object target, int damage);

int perform(object me, object target)
{
        object du;
        int damage;
        string msg, msg1;
        int ap, dp, lvl, fmsk;
        int delta;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("你只能对战斗中的对手施展" + name() + "。\n");

        if ((int)me->query_skill("chousui-zhang", 1) < 220)
                return notify_fail("你的抽髓掌火候不够。\n");

        if ((int)me->query_skill("poison", 1) < 250)
                return notify_fail("你的基本毒技火候不够。\n");

        if ((int)me->query_skill("huagong-dafa", 1) < 220)
                return notify_fail("你的化功大法火候不够。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的内力修为不足，无法用内力施展" + name() + "。\n");

        if( query("neili", me)<3000 )
                return notify_fail("你现在内息不足，无法用内力施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "chousui-zhang")
                return notify_fail("你还没有准备抽髓掌，无法施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "只见$N" HIR "双目血红，头发散乱，猛地仰天发出一声悲啸。\n\n"
              "$N" HIR "把心一横，在自己舌尖狠命一咬，将毕生功力尽"
              "数喷出，顿时只见空气中血雾弥漫，腥臭无比，随即又\n"
              "听$N" HIR "骨骼“噼里啪啦”一阵爆响，双臂顺着喷出的"
              "血柱一推，刹那间一座丈来高的奇毒火墙拔地而起，带\n"
              "着排山倒海之势向$n" HIR "涌去！\n" NOR;
        me->start_busy(2 + random(2));
        addn("neili", -1000, me);

        lvl = me->query_skill("chousui-zhang", 1);
        fmsk = me->query_skill("bingcan-gong", 1);
        damage = damage_power(me, "strike");
        damage+= query("jiali", me);
        damage+= me->query_all_buff("unarmed_damage");
        damage+= damage / 300 * me->query_str();

        delta = ABILITY_D->check_ability(me, "da_power-csz-tao"); 
        if( delta ) damage += damage*delta/100;

        ap = attack_power(me, "strike") +
             me->query_skill("poison", 1);
        dp = defense_power(target, "dodge") +
             target->query_skill("force", 1)/2;
        
        delta = ABILITY_D->check_ability(me, "ap_power-csz-tao"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        if (ap + random(ap) < dp)
        {
                msg += CYN "$n" CYN "见势不妙，急忙腾挪身形，避开了$N" CYN "的攻击。\n" NOR;
                // me->addn("max_neili", -random(50));
                if (! target->is_busy())
                        target->start_busy(3);
        } else
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90+fmsk/10, (: attack,me,target,damage :));

                target->affect_by("fire_poison",
                               (["level":query("jiali", me)*6+random(query("jiali", me)*4),
                                  "id":query("id", me),
                                  "duration" : lvl / 20 + random(lvl) ]));
                if (! target->is_busy())
                        target->start_busy(5);
        }

        message_vision(msg, me, target);

        return 1;
}
string attack(object me, object target, int damage)
{
        mapping buff, data;
        string msg;

        msg = HIR "$n" HIR "见滔天热浪扑面涌来，只觉眼前一片通红，"
                       "已被卷入火浪，毒焰席卷全身，连骨头都要烤焦一般。\n" NOR;

        if( random(2) != 1 ) return msg;
        
        data = ([
                "avoid_poison": -90,

        ]);
        buff = ([
                "caster": me,
                "target": target,
                "type"  : "chousui-zhang_tao",
                "attr"  : "curse",
                "name"  : "碧焰滔天·毒火攻心",
                "time"  : 200,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : HIG "你只觉得心胸清朗，灵台空明。\n" NOR,
                        
        ]);
        BUFF_D->buffup(buff);

        msg += RED "$n" RED "感到五脏六腑如同烈焰灼烧一般，痛苦万分。\n" NOR;

        return msg;
}

