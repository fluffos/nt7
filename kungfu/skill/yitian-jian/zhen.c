// This program is a part of NT MudLIB
// redl 2014
#include <ansi.h>
#include <combat.h>

#define PNAME NOR "「" HIC "九天伏魔剑阵" NOR "」" NOR

inherit F_SSERVER;

int filter_for_enable(string skill, string skill1) 
{ 
        return (SKILL_D(skill)->valid_enable(skill1) && !SKILL_D(skill)->main_skill()); 
} 

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int att, countlv, c0, c1, damage, i, j, count, sklv, time;
        string *allsk, *sname, skn;
        mapping buff;
        
        if( userp(me) && !query("can_perform/yitian-jian/zhen", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(PNAME "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" PNAME "。\n");

        if ((int)me->query_skill("yitian-jian", 1) < 300)
                return notify_fail("你的倚天剑法不够娴熟，难以施展" PNAME "。\n");

        if ((int)me->query_skill("array", 1) < 150)
                return notify_fail("你的基本阵法不够娴熟，难以施展" PNAME "。\n");

        if ((int)me->query_skill("mahayana", 1) < 600)
                return notify_fail("你的大乘涅磐功不够娴熟，难以施展" PNAME "。\n");

        if ((int)me->query_skill("jingxin", 1) < 150)//基本只能峨眉弟子施展
                return notify_fail("你的静心不够娴熟，难以施展" PNAME "。\n");

        if( query("neili", me)<1500 )
                return notify_fail("你的真气不够，难以施展" PNAME "。\n");

        if (me->query_skill_mapped("sword") != "yitian-jian")
                return notify_fail("你没有激发倚天剑法，难以施展" PNAME "。\n");

        if (me->query_skill_mapped("force") != "linji-zhuang")
                return notify_fail("你没有激发临济十二桩，难以施展" PNAME "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        if( (time = BUFF_D->get_buff_overtime(me, "emaq_fumojianzhen")) > 0 )
                                return notify_fail(MAG"九天伏魔剑阵消耗心神太甚，还需等待"+time+"秒。\n"NOR);


                allsk = keys(me->query_skills());
                sname = filter_array(allsk, (: filter_for_enable :), "sword"); 
                sname -= ({"yitian-jian"});
                j = sizeof(sname);
                if (userp(me) && (j > (me->query_skill("array") / 150)))
                        j = me->query_skill("array") / 150;
                if (j) {
                        if (j > 9) j = 9; 
                msg = HIY "\n$N" HIY "运转倚天剑法，将手中的" + weapon->name() + HIY "往地上一掷，“锵”得一声剑鸣，\n只见" +
                                        weapon->name() + HIY "依照大九天伏魔阵势，分化为" + chinese_number(j) + "道剑光，从四方朝$n" HIY "笼罩而去！\n" NOR;
                        addn("can_perform/yitian-jian/zhen", 1, me);
                //message_combatd(msg, me, target); 
                message_vision(msg, me, target);
                        count = me->query_skill("sword", 1) / 2 * query("level", me);
//                        count = count * (1 + query("can_perform/yitian-jian/zhen", me) /5)
                        if( BUFF_D->check_buff(me, "ljz_fengyun") )
                                count *= 2;
                        addn_temp("apply/attack", count, me); 
                        c0 = me->query_skill("count", 1);
                        c1 = me->query_skill("count", 1) - me->query_skillo("count", 1);
                                                countlv = 0;
                                                if (query("can_perform/yitian-jian/zhen", me) >= 5) 
                                                countlv = query("can_perform/yitian-jian/zhen", me) * 100;
                                                if (countlv) me->set_skill("count", c0 + countlv);
                        
                        for (i=0; i<j; i++){
                                if (! me->is_fighting(target)) 
                                        break; 
                                        if( !weapon || !objectp(weapon) || !environment(weapon) || environment(weapon) != me || weapon!=query_temp("weapon", me))
                                                        break;
                                skn = sname[random(sizeof(sname))];
                                sname -= ({skn});
                                sklv = me->query_skill(skn, 1);

                                        ap = sklv * 2;
                                        ap = ap + (ap * me->query_skill("jingxin", 1) / 150);
                                        ap = ap + (ap * me->query_skill("array") / 500);
                                        dp = target->query_skill("force",1) + target->query_skill("parry",1) + target->query_skill("dodge",1);
                                        dp = dp + (dp * target->query_skill("array") / 350);

                                msg = "\n" + PNAME + NOR HIC + to_chinese(skn) + NOR HIC + "，\n" NOR;
                                //message_combatd(msg, me, target); 
                                message_vision(msg, me, target);
                                if (ap / 2 + random(ap) > dp) {
                                        me->map_skill("sword", skn);
                                        me->reset_action();
                                        damage = sklv * query("jiali", me) / 1000 + me->query_skill("mahayana") + me->query_all_buff("damage");
                                        damage = damage + damage * i / 18;
                                        att = pow(sklv, 1.5);
                                        att += att * query("can_perform/yitian-jian/zhen", me) / 100;
                                        addn_temp("apply/attack", att, me); 
                                        addn_temp("apply/damage", damage, me); 
                                        COMBAT_D->do_attack(me, target, weapon, TYPE_LINK); 
                                        addn_temp("apply/damage", -damage, me); 
                                        addn_temp("apply/attack", -att, me); 
                                } else {
                                                msg = CYN "可是$n" CYN + (random(2) ? "轻轻一跃" : "鼓劲硬抗") + "，" 
                                        + (random(2) ? "避开了" : "躲过了") + PNAME + HIC + to_chinese(skn) + NOR CYN "的攻击范围。\n"NOR;
                                        message_combatd(msg, me, target); 
                                }
                                addn("neili", -500, me);
                        }
                                                
                                                if (countlv) {
                                                        if (c1 > me->query_skill("count", 1) - me->query_skillo("count", 1))
                                                                {
                                                                        c0 = c0 - (c1 - (me->query_skill("count", 1) - me->query_skillo("count", 1)));
                                                                }
                                                        me->set_skill("count", c0);
                                                        if (c0<1) me->delete_skill("count"); 
                                                }
                        
                        me->map_skill("sword", "yitian-jian");
                        me->reset_action();
                        addn_temp("apply/attack", -count, me); 
                                                if (query("can_perform/yitian-jian/zhen", me) == 5 || (query("can_perform/yitian-jian/zhen", me) & 50) == 0 ) {
                                                    tell_object(me, HIC "你领悟了"HIY"「九天伏魔剑阵」"HIC"击破特防的诀窍，继续加深熟练度吧。\n" NOR); 
                                                    set("can_perform/yitian-jian/zhen", 30, me);
                                                if (me->can_improve_skill("sword")) 
                                                        me->improve_skill("sword", 1500000); 
                                                if (me->can_improve_skill("yitian-jian")) 
                                                        me->improve_skill("yitian-jian", 1500000); 
                                        me->improve_skill("martial-cognize", 1000000); 
                                        me->improve_skill("sword-cognize", 1500000); 
                                                }
                } else {
                        tell_object(me, NOR "你修为不足，运转" + PNAME + NOR "失败。\n" NOR);
                        me->start_busy(2);
                        return 1;
                }
                me->start_busy(6 + random(3));
                if (!target->is_busy()) target->start_busy(3);

                time = 60;
                time -= query("level", me) / 20;
                if (time < 45) time = 45;
                //if ( BUFF_D->check_buff(me, "ljz-niepan") ) time -= 5;
                if( BUFF_D->check_buff(me, "ljz_fengyun") ) time -= 5;
                buff = ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "emaq_fumojianzhen",
                "attr"   : "curse",
                "name"   : "倚天剑法·九天伏魔剑阵",
                "time"   : time,
                "buff_msg" : "九天伏魔剑阵消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
                ]);
                BUFF_D->buffup(buff);
                
                if( weapon && objectp(weapon) && environment(weapon) ) {
                        weapon->move(environment(me));
                        set("who_get/id", query("id", me), weapon);
                        set("who_get/time", time() + 30, weapon);
                        msg = HIY "\n" HIY + weapon->name() + HIY "钉在地上哀鸣一声，像在等待$N" + HIY + "的召唤。\n\n" NOR;
                message_vision(msg, me);
                }
                
        return 1;
}

