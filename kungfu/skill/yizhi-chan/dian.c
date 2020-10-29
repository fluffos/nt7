// This program is a part of NITAN MudLIB
// dian.c 指点江山

#include <ansi.h>

inherit F_SSERVER;
string name() { return "指点江山"; }

int perform(object me, object target)
{
        object weapon;
        object ob;              // 对手的武器
        string msg;
        int ap, dp, fingerlv,lvl;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("绝技「指点江山」只能对战斗中的对手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                        return notify_fail("你不能使用武器！\n");


        if( (int)me->query_skill("yizhi-chan", 1) < 150 )
                return notify_fail("你的一指禅太生疏，不会使用「指点江山」。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够，现在无法使用「指点江山」。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        addn("neili", -100, me);

        msg = HIY " $N深深吸了一口气，伸出中指，使出佛门伏魔无上绝技指法，慢慢得向$n点了过去。\n";

        ob=query_temp("weapon", target);
        ap = attack_power(me, "finger");
        ap += 20 * (int)me->query_skill("martial-cognize", 1);
        if (playerp(me) && (int)me->query_skill("buddhism", 1) > 3000)
        ap *= (int)me->query_skill("buddhism", 1) / 3000;
        ap += ap * (int)me->query_skill("lunhui", 1) / 1000;
        dp = defense_power(target, "force");
        dp += dp * (int)target->query_skill("buddhism", 1) / 6000; 

        if (ap / 2 + random(ap) > dp)
        {
                if (! objectp(ob))
                {
                        int damage = 0;
                        fingerlv = me->query_skill("yizhi-chan") / 3;
                        lvl = (int)me->query_skill("buddhism", 1)/10000;
                        if(lvl<0)lvl=0;
                        if(lvl>6)lvl=6;
                        if (playerp(me)) fingerlv *= random(91) + 10;

                        if ((random(target->query_skill("dodge")) > fingerlv) && random(2) == 0)
                        {
                                switch (random(2))
                                {
                                case 0:
                                        msg += HIR " $n连续变了几种上乘身法，终于没能躲过，"
                                                "$N的这一指正点在$n的丹田上，\n$n只觉得一口"
                                                "凉气，自丹田而上，心里有种说不出的难受。\n";
                                        damage = 3;
                                        if ((int)me->query_skill("lunhui", 1) > random(2000)) damage += 1; 
                                        break;
                                case 1:
                                        msg += HIR " $n轻身飘开，身法灵动之极，众人正要喝彩，"
                                                "听「噗」的一声，如击败革，$n脸色煞白，摇摇欲坠。\n";
                                        damage = 5;
                                        if ((int)me->query_skill("lunhui", 1) > random(2000)) damage += 1; 
                                        break;
                                }
                        } else
                        if ((random(target->query_skill("force")) > fingerlv) && random(2) == 0)
                        {
                                switch(random(2))
                                {
                                case 0:
                                        msg += HIR " $n冷哼一声，自持内力高强，反手出招，「啵」"
                                                "的一声二指相交，$n身行微晃，脸如金纸。\n";
                                        damage = 3;
                                        if ((int)me->query_skill("lunhui", 1) > random(2000)) damage += 1; 
                                        break;
                                case 1:
                                        msg += HIR " $n一声长啸，双手幻化出无数掌影，护住身前。"
                                                "只听「嗤」的一声，掌影顿消，$n已经变得脸色惨白。\n";
                                        damage = 4;
                                        if ((int)me->query_skill("lunhui", 1) > random(2000)) damage += 1; 
                                        break;
                                }
                        } else
                        {
                                switch(random(2))
                                {
                                case 0:
                                        msg += HIR " $n看到这招，竟然不知躲避，「嗤」的一声，$N"
                                                "这一指正点在$n的檀中大穴。\n";
                                        damage = 0;
                                        break;
                                case 1:
                                        msg += HIR " $n一转念，已经想出了九十九种化解的办法，"
                                                "尚未来得及施展，只听「嗤」的一声，已被$N点中檀"
                                                "中大穴。\n";
                                        damage = 0;
                                        break;
                                }
                        }
                        message_combatd(msg + NOR, me, target);
//                        if (damage > 0)
                        if (damage > 0 || (playerp(target) && random(3)))
                        {
                                if (damage < 1) damage = 6;
                                 target->receive_damage("qi",query("max_qi", target)/12*damage,me);
                                COMBAT_D->report_status(target);
                        }
                       else if(random(me->query_skill("buddhism",1))>10000 && me->query_skill("lunhui", 1) > random(2000))
                             target->receive_damage("qi",query("max_qi", target)*(damage+lvl)/12,me);
                        else     
                             target->unconcious(me);

                        if( objectp(me) ) me->start_busy(2);
                        return 1;
                }
                if (ob->is_item_make() || query("bak_name", ob))
                {
                        ob->move(environment(target));
                        //set("consistence", 0, ob);
                        msg+=HIR"$n忙用"+query("name", ob)+"招架，只觉得虎口剧震，兵器脱手而出！。\n"NOR;
                } else
                {
                        msg += HIW " $n连忙招架，只听见「啪」地一声，$n手中的" + ob->name()
                                + "寸寸断裂，散落一地！\n";
                        ob->unequip();
                        ob->move(environment(target));
                        set("name", "断掉的"+query("name", ob), ob);
                        set("value", 0, ob);
                        set("weapon_prop", 0, ob);
                }
                me->start_busy(2);
                if (! target->is_busy()) target->start_busy(ap/120 + 2);
        } else
        {
                int busy = 0;
                if ((random(target->query_skill("dodge")) > fingerlv) && random(2) == 0)
                {
                        switch (random(2))
                        {
                        case 0:
                                msg += " $n一声轻笑，连续变化了几次身法，扰人耳目，一时让$N无法进攻。\n";
                                busy = 2;
                                break;
                        case 1:
                                msg += " $n突然向后飘去，疾若闪电，令$N这一指所有的后继变化无从施展。\n";
                                busy = 1;
                                break;
                        }
                } else
                if ((random(target->query_skill("force")) > fingerlv) && random(2) == 0)
                {
                        switch (random(2))
                        {
                        case 0:
                                msg += " $n脸色凝重，缓缓出掌，以拙对拙，竟然让$N无从下手，只得收指。\n";
                                busy = 3;
                                break;
                        case 1:
                                msg += " $n满脸不屑，冷笑一声，双掌齐出，其快无比，令$N只能回招自救。\n";
                                busy = 1;
                                break;
                        }
                } else
                {
                        switch (random(3))
                        {
                        case 0:
                                msg += " $n左摇右晃，看上去毫无章法，偏偏躲过了$N这一击。\n";
                                busy = 2;
                                break;
                        case 1:
                                msg += " $n一指点出，看上去恍若也是佛门精妙指法，$N一呆，攻势顿缓。\n";
                                busy = 2;
                                break;
                        case 2:
                                if (objectp(ob))
                                msg+="$n摄住心神，真气贯注"+query("name", ob )
                                         + "，堪堪封住了$N的进攻。\n";
                                else
                                msg += "$n摄住心神，真气贯注双掌，堪堪封住了$N的进攻。\n";
                                busy = 2;
                                break;
                        }
                }
                if (! target->is_busy())
                        target->start_busy(busy);
                me->start_busy(3+random(2));
        }
        message_combatd(msg + NOR, me, target);

        return 1;
}

