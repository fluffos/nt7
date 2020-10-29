
// This program is a part of NITAN MudLIB
// hun.c 剑魂

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIM "剑魂" NOR; }

int can_not_hubo() { return 1;}

private int remove_attack(object me, object weapon);

int perform(object me, object target)
{
        string *limbs, limb;
        string msg;
        object *ob, weapon;
        mapping buff;
        int ap, dp, count, p;
        int skill;
        int i, damage;
        int time;
        int delta;
        int fmsk = me->query_skill("jianyi", 1);

        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你尚未悟道，无法施展" + name() + "。\n");

        /*
        if( query("family/family_name", me) != "华山派"
         && member_array("华山派", query("reborn/fams", me)) == -1 )
                return notify_fail("你尚未转世重生，无法施展" + name() + "。\n");

        if( query("family/family_name", me) != "华山派" )
                return notify_fail("你不是华山派弟子，无法施展" + name() + "。\n");
        */
        /*
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail(HUN "只能对战斗中的对手使用。\n");
        */

        if( !me->is_fighting() )
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("dugu_jianhun", me) || BUFF_D->check_buff(me, "protect") )
                return notify_fail("你已在使用" + name() + "了！\n");

        weapon=query_temp("weapon", me);
        if( !objectp(weapon) || query("skill_type", weapon) != "sword" )
                return notify_fail("你手中无剑，如何能够施展" + name() + "？\n");

        if( (int)me->query_skill("lonely-sword", 1) < 1000 )
                return notify_fail("你的独孤九剑不够娴熟，难以施展" + name() + "。\n");

        if( me->query_skill("force") < 1200 )
                return notify_fail("你的内功火候未到，无法配合杖法施展" + name() + "！\n");

        if( me->query_skill("sword", 1) < 1000 )
                return notify_fail("你剑法修为不足，还不会使用" + name() + "！\n");

        if( me->query_skill("sword-cognize", 1) < 500 )
                return notify_fail("你剑道修养火候未到，还不会使用" + name() + "！\n");

        if( me->query_skill("martial-cognize", 1) < 500 )
                return notify_fail("你武学修养火候未到，还不会使用" + name() + "！\n");

        if( query("neili", me) <= 1000 )
                return notify_fail("你的内力不够施展" + name() + "！\n");

        if( query("jingli", me) <= 500 )
                return notify_fail("你的精力不够施展" + name() + "！\n");

        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "dgjj_hun")) > 0 )
                        return notify_fail(MAG"剑魂消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }
        
        count = me->query_skill("sword-cognize", 1) + me->query_skill("martial-cognize", 1);
        count /= 500;

        msg = HIW "$N" HIW "神态写意，温柔抚弄手中的" + weapon->name() + HIW "，只见" + weapon->name() +
              HIW "表面掠过一丝光影，微微颤动，整把剑竟灵动起来、有若生物。\n" NOR
              HIM"$N"HIM"将手中"+query("name", weapon)+HIM"缓缓刺出，剑招随意无章！\n"NOR
              HIM "这招看似缓慢，其实疾如闪电，看似随意无章，却是和" + weapon->name() + HIM "融为一体，无懈可击，蕴涵着返璞归真的意境。\n" NOR;

        message_combatd(msg, me);

        damage = damage_power(me, "sword");
        damage += me->query_all_buff("damage");
        damage += query("jiali", me);
        damage += damage / 300 * me->query_str();
        damage *= 9;
        delta = ABILITY_D->check_ability(me, "da_power-dgjj-hun"); // 门派ab
        if( delta ) damage += damage*delta/100;
        
        ap = attack_power(me, "sword") +
             me->query_skill("dodge");

        ap = ap + ap * fmsk / 1000; 
        
        delta = ABILITY_D->check_ability(me, "ap_power-dgjj-hun"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        ob = me->query_enemy();
        skill = me->query_skill("lonely-sword", 1);
        
        for (i = 0; i < sizeof(ob); i++)
        {
                dp = defense_power(ob[i], "parry") +
                     ob[i]->query_skill("dodge");

                if (ap * 2 / 3 + random(ap) > dp)
                {
                        ob[i]->receive_damage("qi", damage, me);
                        ob[i]->receive_wound("qi", damage / 2, me);
                        ob[i]->set_weak(5);
                        set("neili", 0, ob[i]);
                        set("jiali", 0, ob[i]);
                        ob[i]->apply_condition("no_exert", 3);
                        ob[i]->apply_condition("no_perform", 3);

                        msg = HIR "$n" HIR "想招架却感无从招架，想躲避也感到无处可躲，登时被$N" HIR "一剑划过，\n"
                              HIR "遭受重创，一阵锥心的刺痛，全身真气源源而泻！\n" NOR;

                        if( delta = ABILITY_D->check_ability(me, "fatal_blow-dgjj-hun") ) // 门派ab
                        {
                                if( random(10) < delta )
                                {
                                        ob[i]->receive_damage("qi", damage*10, me);
                                        ob[i]->receive_wound("qi", damage*10, me);
                                        msg += HIR "紧接着，$N" HIR "追加了致命一击，给$n" HIR "造成更严重的创伤。\n" NOR;
                                }
                        }
                        p=query("qi", ob[i])*100/query("max_qi", ob[i]);
                        msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
                        message_vision(msg, me, ob[i]);
                } else
                {
                        ob[i]->start_busy(2);
                        msg = HIC "$n" HIC "情急之下，不及考虑，倒地一滚，侥幸避开$N" HIC "这一招的攻击，冷汗直淋！\n" NOR;
                        message_vision(msg, me, ob[i]);
                }
        }
        
        set_temp("dugu_jianhun", 1, me);
        addn("neili", -200, me);
        addn("jingli", -100, me);

        msg = HIY "$N" HIY "握紧" + weapon->name() + HIY "向天一指, 叫道 : 剑魂一出 ～ 血光漫天 ～ \n"
              HIY "顿时" + weapon->name() + HIY "剑身化出一道红色的剑形，在天空中恣意飞旋穿梭 ...\n" NOR;

        message_combatd(msg, me);

                if( !objectp(weapon) ) return 1;
                if( query_temp("dugu_jianhun", me) >= count
                ||      !me->is_fighting() )
                {
                                call_out("remove_attack", 0, me, weapon);
                                return 1;
                }

                addn_temp("dugu_jianhun", 1, me);
                message_combatd(HIR "\n剑魂以闪电般的高速在空中穿梭, 以狂乱无比的热情尽情狂舞 ...\n" NOR, me);

                ob = me->query_enemy();
                if( sizeof(ob) < 2 )
                {
                                addn_temp("str", 2000, me);
                                addn_temp("apply/damage", fmsk*20, me);
                                COMBAT_D->do_attack(me, ob[0], weapon, TYPE_LINK);
                                addn_temp("str", -2000, me);
                                addn_temp("apply/damage", -fmsk*20, me);
                                
                } 

                ap = me->query_skill("sword", 1) + me->query_skill("sword-cognize", 1) +
                         me->query_skill("martial-cognize", 1);
                damage=ap+weapon->apply_damage();
                damage += damage_power(me, "sword");
                damage *= 30;
                
                for (i = 0; i < sizeof(ob); i++)
                {
                                if (! objectp(ob[i])) continue;
                                dp=query("parry", ob[i])+
                                                ob[i]->query_skill("dodge", 1);

                                if (dp / 3 + random(dp) < ap)
                                {
                                                limbs=query("limbs", ob[i]);
                                                if (! arrayp(limbs))
                                                {
                                                                limbs = ({ "身体" });
                                                                set("limbs", limbs, ob[i]);
                                                }
                                                limb = limbs[random(sizeof(limbs))];
                                                ob[i]->start_busy(1);
                                                ob[i]->receive_damage("qi", damage, me);
                                                ob[i]->receive_wound("qi", damage / 2, me);
                                                p=query("qi", ob[i])*100/query("max_qi", ob[i]);
                                                msg = COMBAT_D->damage_msg(damage, "割伤");
                                                msg = replace_string(msg, "$l", limb);
                                                msg = replace_string(msg, "$w", weapon->name());
                                                msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
                                                message_combatd(msg, me, ob[i]);
                                }
                }
//        } 
        call_out("remove_attack", 0, me, weapon);

        time  = 40;
        time -= ABILITY_D->check_ability(me, "cd-dgjj-hun"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd  
        if(wizardp(me) && query("id",me) == "mud") time = 2;     
        buff = ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "dgjj_hun",
                "attr"   : "curse",
                "name"   : "独孤九剑·剑魂",
                "time"   : time,
                "buff_msg" : "剑魂消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
        ]);
        
        BUFF_D->buffup(buff);
        me->start_busy(2);
        
        return 1;
}

int remove_attack(object me, object weapon)
{
        if( !objectp( me ) ) return 1;
        if( !query_temp("dugu_jianhun", me))return 1;

        delete_temp("dugu_jianhun", me);
        if( !weapon ) return 1;
        message_combatd(HIW "一阵狂舞之后, 剑魂又自动飞入你的手中" + weapon->name() + HIW " ...\n" NOR, me);

        return 1;

}
