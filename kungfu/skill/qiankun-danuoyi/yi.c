// This program is a part of NITAN MudLIB
// yi.c 大挪移

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "大挪移"; }

int perform(object me, object target)
{
        object weapon;
        object *obs;
        object der;
        string msg;
        int ap, dp;
        int damage;
        int level;
        int i;
        int delta;

        me->clean_up_enemy();
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「大挪移」只能对战斗中的对手使用。\n");

        if ((level = (int)me->query_skill("qiankun-danuoyi", 1)) < 50)
                return notify_fail("你的乾坤大挪移还没有修炼到第二层，无法施展大挪移。\n");

        if (query("neili", me) < 400)
                return notify_fail("你现在真气不够，无法使用「大挪移」。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIM "$N" HIM "招数忽然的一变，摹可明方，内力四处回旋，无形中牵引着$n"
              HIM "的招式！\n";

        //ap = attack_power(me, "parry");
        ap = attack_power(me, "unarmed");
        ap = ap * 3 / 2;
        dp = defense_power(target, "dodge");

        delta = ABILITY_D->check_ability(me, "ap_power-qkdny-yi"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        if (level >= 300)
        {
                // layer 7 force
                ap += level;
                ap += level*10;
        }

/*
        if (ultrap(target))
                dp += target->query_skill("matrial-cognize", 1);
*/

        der = 0;
        me->start_busy(2+random(2));
        addn("neili", -350, me);
        if (ap *2/ 3 + random(ap) > dp)
        {
                // Success to make the target attack hiself
/*
                msg += HIR "结果$p" HIR "一招击出，正好打在自己的"
                       "要害上，不禁一声惨叫，摔跌开去。\n" NOR;
*/
                // damage = target->query("max_qi");
                damage = damage_power(me, "parry");
                damage+= query("jiali", me);
                damage *= 20;
                damage += random(damage);
                
                delta = ABILITY_D->check_ability(me, "da_power-qkdny-yi"); // 门派ab
                if( delta ) damage += damage*delta/100;
        
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 300, 
                                          HIR "结果$n" HIR "一招击出，正好打在自己的"
                                          "要害上，不禁一声惨叫，摔跌开去。\n" NOR);

/*
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage / 2, me);
*/
        } else
        if (ap / 2 + random(ap) < dp)
        {
                // The enemy has defense
                msg += CYN "然而$p" CYN "内功深厚，并没有被$P"
                       CYN "这巧妙的劲力所带动。\n" CYN;
        } else
        if (sizeof(obs = me->query_enemy() - ({ target })) == 0)
        {
                // No other enemy
                msg += HIC "结果$p" HIC "的招式莫名其妙的变"
                       "了方向，竟然控制不住！幸好身边没有别"
                       "人，没有酿成大祸。\n" NOR;
        } else
        {
                string pname;
                // Sucess to make the target attack my enemy
                der = obs[random(sizeof(obs))];
                pname = der->name();
                if (pname == target->name()) pname = "另一个" + pname;
                msg += HIG "结果$p" HIG "发出的招式不由自主"
                       "的变了方向，突然攻向" + pname + HIG "，不禁令" +
                       pname + HIG "大吃一惊，招架不迭！" NOR;
        }

        message_combatd(msg, me, target);

        if (der)
        {
                // Target attack my enemy
                for (i = 0; i < 2 + random(3); i++)
                {
                        if (! der->is_busy()) der->start_busy(2);
                        COMBAT_D->do_attack(target, der, query_temp("weapon", target));
                }
        }

        return 1;
}
