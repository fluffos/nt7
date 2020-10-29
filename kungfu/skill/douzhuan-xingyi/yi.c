// yi.c 斗转星移
// mud updated on 25th,Feb,2015
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "斗转星移"; }
string *limbs = ({"头部", "颈部", "胸口", "后心","小腹",});
mapping weap =
        (["sword":"剑","blade":"刀","whip":"鞭",
        "club":"棍","staff":"棒","hammer":"锤",
        "throwing":"暗器","dagger":"匕",]);
int perform(object me, object target)
{
        object weapon, weapon2;
        object *obs;
        object der;
                mapping prepare;
        string msg,action,limb, wob, wme,wmsg;
        int ap, dp;
        int damage,wounded,dam,flag;
        int i;
        int delta;
        int zihui, fmsk = me->query_skill("huitong-tianxia", 1);
                string attack_skill, martial_skill;
        int time;
        mapping buff,act;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「斗转星移」只能对战斗中的对手使用。\n");

        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你尚未悟道，无法使用"+name()+"。\n");

        if ((int)me->query_skill("douzhuan-xingyi", 1) < 1000)
                return notify_fail("你的斗转星移不够娴熟，不会使用绝招。\n");

        if ((int)me->query_skill("zihui-xinfa", 1) < 1000)
                return notify_fail("你的紫徽心法修为还不到家，难以运用「斗转星移」。\n");

        if( query("neili", me)<600 )
                return notify_fail("你现在真气不够，无法使用「斗转星移」。\n");

        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        if( userp(me) )
        {
                if( (time = BUFF_D->get_buff_overtime(me, "dzxy_yi")) > 0 )
                        return notify_fail(MAG"斗转星移消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }

        prepare = target->query_skill_prepare();
        if( !prepare ) prepare = ([]);

        weapon = query_temp("weapon", target);
        weapon2 = query_temp("weapon", me);

        if( objectp(weapon) )
                {
                    attack_skill = query("skill_type", weapon);
                        wob = weap[attack_skill];
                        if(objectp(weapon2) && attack_skill != query("skill_type",weapon2))
                        {
                           wme = weap[query("skill_type",weapon2)];
                           wmsg = "$N驭气于"+weapon2->name()+"，化"+wme+"为"+wob+"。\n";
                           wme = weapon2->name();
                         }
                        if(!objectp(weapon2))
                        wme = HIW+BLINK"无形真气"NOR;
                }
        else if(  sizeof(prepare) == 0) attack_skill = "unarmed";
        else if(  sizeof(prepare) == 1) attack_skill = (keys(prepare))[0];
        else if(  sizeof(prepare) == 2) attack_skill = (keys(prepare))[query_temp("action_flag", target)];

        if( attack_skill == "pin" )
            attack_skill = "sword";

                martial_skill = target->query_skill_mapped(attack_skill);
        if( !martial_skill )
                martial_skill = attack_skill;

                if( martial_skill == "six-finger"
         ||     martial_skill == "dragon-strike"
         ||     martial_skill == "dagou-bang"
         ||     martial_skill == "sun-finger")
        flag = 1;

                if( SKILL_D(martial_skill)->is_shaolin_skill())
                flag = 2;

                limb = limbs[random(sizeof(limbs))];
        msg = HIG "$N" HIG "施展起绝学「斗转星移」，以彼之道，还施彼身！\n"NOR;
                msg+= HIG "$N"NOR+HIG"冷笑一声，仿佛洞彻了$n"NOR+HIG"的成名绝技------"+HIR+to_chinese(martial_skill)+HIG+"!\n";
                msg+= HIG"赫然使出了"+HIR+to_chinese(martial_skill)+HIG+"，好似毕生钻研一般。\n"NOR;
                if(stringp(wmsg))
                msg+= wmsg;
                act = SKILL_D(martial_skill)->query_action(target,weapon);
                if(act)
                {
                   action = act["action"];
                   msg+= action+"\n";
                   if(wme)
                   msg = replace_string(msg,"$w",wme)+"!\n";
                   msg = replace_string(msg,"$l",limb)+NOR;
                }
        ap = attack_power(me, "force");
        dp = defense_power(target, "parry");

        zihui = me->query_skill("zihui-xinfa", 1);
                zihui+= me->query_skill("shenyuan-gong", 1);
                zihui = zihui / 5000;
                ap = ap + ap /10 * zihui;
        ap = ap + ap /1000 * fmsk;
        if(flag == 1) ap = ap - ap/5;
                if(flag == 2) ap = ap + ap/5;

        delta = ABILITY_D->check_ability(me, "ap_power-dzxy-yi"); // 门派ab
        if( delta ) ap += ap*delta/100;

        der = 0;
        me->start_busy(2);
        addn("neili", -50, me);
                if (ap/2 > dp && query("combat_exp",me) /10 > query("combat_exp",target))
                {
                    msg+= HIK"$n眼见$N使出自己毕生所学，万念俱灰，坐以待毙。\n"NOR;
                        message_combatd(msg, me, target);
                        target->receive_damage("qi", 100, me);
                        target->die(me);
                }

        else if (ap > dp /10 * 12)
        {
                // Success to make the target attack hiself
            msg += HIK "结果$N" HIK "一招击出，正好打在$n的"+limb+"上，$n不禁一声惨叫，摔跌开去。" NOR;
            dam = query("max_qi", target);
            damage = target->receive_damage("qi", dam / 2, me);
            wounded = target->receive_wound("qi", dam / 2, me);
                        message_combatd(msg, me, target);
            message_combatd(COMBAT_D->report_status(target,1), target, me);
                        if( userp(me) )
                tell_object(me, HIW "( 你对" +
                                        query("name", target)+HIW"造成"+
                                        damage + "点伤害，" +
                                        wounded + "点创伤。)\n" NOR);
            if( userp(target) )
                     tell_object(target, HIG "( 你受到" +
                                        query("name", me)+HIG+damage+"点伤害，"+
                                        wounded + "点创伤。)\n" NOR);

        }
                else if (ap / 2 + random(ap) < dp)
        {
                // The enemy has defense
                msg += CYN "然而$p" CYN "内功深厚，并没有被$P"
                       CYN "这巧妙的劲力所带动。\n" CYN;
                            message_combatd(msg, me, target);
        }
                else if (sizeof(obs = me->query_enemy() - ({ target })) == 0)
        {
                // No other enemy
                msg += HIC "结果$p" HIC "的招式莫名其妙的变"
                       "了方向，竟然控制不住！幸好身边没有别"
                       "人，没有酿成大祸。\n" NOR;
                            message_combatd(msg, me, target);
        }
                else
        {
                string name;
                // Sucess to make the target attack my enemy

                der = obs[random(sizeof(obs))];
                name = der->name();
                if (name == target->name()) name = "另一个" + name;
                msg += HIG "结果$p" HIG "发出的招式不由自主"
                       "的变了方向，突然攻向" + name + HIG "，不禁令" +
                       name + HIG "大吃一惊，招架不迭！" NOR;
                            message_combatd(msg, me, target);
        }

        if (der)
        {
                // Target attack my enemy
                for (i = 0; i < 2 + random(3); i++)
                {
                        if (! der->is_busy()) der->start_busy(1);
                        COMBAT_D->do_attack(target,der,query_temp("weapon", target),TYPE_LINK);
                }
        }
        time = 38;
        time -= ABILITY_D->check_ability(me, "cd-dzxy-yi"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd
        if(wizardp(me) && query("id",me) =="mud") time =2;
        buff = ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "dzxy_yi",
                "attr"   : "curse",
                "name"   : "斗转星移·斗转星移",
                "time"   : time,
                "buff_msg" : "斗转星移消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
        ]);

        BUFF_D->buffup(buff);
        return 1;
}
