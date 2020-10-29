#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR"灰飞湮灭"NOR; }

#include "/kungfu/skill/eff_msg.h";
string final(object me, object target, int lvl);

int perform(object me, object target)
{
        string msg;
        int ap, dp, flvl, add_lvl, fmsk;
        int damage, add_dam;
        int is_jifa_beiming;
        int delta,flagremote;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("「灰飞湮灭」只能空手才能施展。\n");

        if (! me->is_fighting(target))
                return notify_fail("「灰飞湮灭」只能对战斗中的对手使用。\n");

        if (! target || ! target->is_character())
                return notify_fail("你要对谁施展灰飞湮灭？\n");

        if (! living(target))
                return notify_fail("看清楚，那不是活人。\n");

        if (me->query_skill_prepared("strike") != "liuyang-zhang" )
                return notify_fail("你还没有将天山六阳掌与逍遥折梅手互备，无法施展。\n");

        if (me->query_skill_prepared("hand") != "zhemei-shou" )
                return notify_fail("你还没有将天山六阳掌与逍遥折梅手互备，无法施展。\n");

        if (me->query_skill_mapped("dodge") != "lingbo-weibu" )
                return notify_fail("你还没有激发凌波微步，无法施展。\n");

        if( query("neili", me)< query("max_neili",me)/35 )
                return notify_fail("你的真气不够，现在无法施展灰飞湮灭。\n");

        msg = HIY "$N" HIY "左手化掌，右手成刀，不停翻转向前，掌风到处，一股紫气席卷而至，将$n" HIY "四周包围。\n" NOR;

        ap = attack_power(me, "strike") + me->query_skill("hand");
        dp = defense_power(target, "parry") + target->query_skill("unarmed");
        
        delta = ABILITY_D->check_ability(me, "ap_power-lyz-hui"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        fmsk = me->query_skill("xiaoyao_you",1);
        
        flvl = query("jiali", me);
        add_lvl = flvl * 3;
        add_dam = 100;

        is_jifa_beiming = me->query_skill_mapped("force") == "beiming-shengong" ? 1 : 0;

        if (ap / 2 + random(2*ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);
                damage+= me->query_all_buff("unarmed_damage");
                damage+= damage / 300 * me->query_str();  
                
                delta = ABILITY_D->check_ability(me, "da_power-lyz-hui"); // 门派ab
                if( delta ) damage += damage*delta/100;
                
                flagremote = UNARMED_ATTACK;
                if( fmsk > 1500 && me->query_skill("beiming-shengong",1) > 7500)
                 flagremote = SPECIAL_ATTACK;
                if( fmsk > 2000 && me->query_skill("beiming-shengong",1) > 15000)
                  flagremote = REMOTE_ATTACK;
                
                // 如激发beiming-shengong 有1/3机会内力迸发
                if (random(3) == 1 && is_jifa_beiming)
                {
                        msg += HIW "刹那间，$N" HIW "只觉体内北冥真气犹如火山喷发般汹涌而出，周身"
                                   "穴位中融和了无数武学高手不同宗派的内力，顷刻间涌出，游走至双掌"
                                    "，泛出炽热的白光 ……\n" NOR;
                        msg = sort_msg(msg);

                        add_dam = 400;
                }

                // 离开逍遥派后威力减半
                if( !(query("family/family_name", me) ||
                    query("family/family_name", me) != "逍遥派") && (!query("reborn/times", me) || 
                    member_array("逍遥派", query("reborn/fams", me)) == -1) ) 
                {
                        damage /= 2;
                        add_dam /= 2;
                }

                if( random(5) == 1 && query("can_perform/liuyang-zhang/zhong", me) )
                {
                        msg += COMBAT_D->do_damage(me, target, flagremote, damage, add_dam+fmsk/10,
                                                   (: final, me, target, add_lvl :));
                }
                else
                {
                        msg += COMBAT_D->do_damage(me, target, flagremote, damage, add_dam+fmsk/10,
                                                   HIR "只见风沙漫天,忽地一掌正中$n" HIR "胸口，随即"
                                                   "闷哼一声，鲜血狂喷而出。\n" NOR);
                }

                addn("neili", -query("max_neili", me)/40, me);
                if (me->query_skill("lingbo-weibu", 1) >= 1500 && random(100) < 15)
                {
                        message_combatd(HIW "$N" HIW "默念凌波微步口诀，身法忽快，丝毫不受出招的阻碍。\n" NOR, me);
                }
                else
                {
                        me->start_busy(2);
                }
        } else
        {
                msg += CYN "可是$p" CYN "身法突变，左躲右闪，竟避过这招。\n" NOR;
                if (me->query_skill("lingbo-weibu", 1) >= 1500 && random(100) < 15)
                {
                        message_combatd(HIW "$N" HIW "默念凌波微步口诀，身法忽快，丝毫不受出招的阻碍。\n" NOR, me);
                }
                else
                {
                        me->start_busy(3);
                }
                addn("neili", -2500, me);
        }

        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int lvl)
{
          target->affect_by("ss_poison",
                       ([ "level"    : lvl,
                          "id":query("id", me),
                          "duration" : 120 + random(240)]));

          if( random(5) == 1)set("neili", 0, target);

          if (! target->is_busy()) target->start_busy(2 + random(5));

          return HIR "$n" HIR "只觉得一股寒气透心而过，犹如利刃穿心，难受之极。\n" NOR;
}

