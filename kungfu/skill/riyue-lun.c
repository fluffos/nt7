// riyue-lun.c 日月轮法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$N使一招"GRN"「破竹势」"NOR"，抡起手中的$w向$n的$l砸去",
        "skill_name" : "破竹势",
        "lvl" : 0
]),
([      "action" : "$N使一招"BLU"「隐山谷势」"NOR"，双肩一沉，舞动手中$w向$n的$l横扫",
        "skill_name" : "隐山谷势",
        "lvl" : 8
]),
([      "action" : "$N使一招"MAG"「隐微势」"NOR"，就地一滚，手中自下而上撩向$n的$l",
        "skill_name" : "隐微势",
        "lvl" : 16
]),
([      "action" : "$N使一招"RED"「擒纵势」"NOR"，身形起伏之际$w扫向$n的$l",
        "skill_name" : "擒纵势",
        "lvl" : 24
]),
([      "action" : "$N使一招"YEL"「圆满势」"NOR"，$w如离弦之箭般直捣$n的$l",
        "skill_name" : "圆满势",
        "lvl" : 32
]),
([      "action" : "$N跃入半空，使一招"HIC"「月重辉势」"NOR"，高举$w敲向$n的$l",
        "skill_name" : "月重辉势",
        "lvl" : 40
]),
([      "action" : "$N使一招"HIW"「捉月势」"NOR"，斜举手中$w击向$n的$l",
        "skill_name" : "捉月势",
        "lvl" : 48
]),
([      "action" : "$N提一口真气，使出"HIR"「显吉祥」"NOR"，$w扫向$n的头部",
        "skill_name" : "显吉祥",
        "lvl" : 56
]),
});
string  *msg = ({
        CYN"空中那五只$w"CYN"对击，声若龙吟，悠悠不绝，就在$n"CYN"一呆之际，$w"CYN"飞砸了出去！"NOR,
        MAG"呜呜声响中，$w"MAG"旋转飞舞着撞向$n"MAG"，在$p"MAG"便要挡隔时，却绕过$n"MAG"飞到了身後"NOR,
        MAG"$w"MAG"连续掷出，连续飞回，绕著$n"MAG"兜个圈子，忽高忽低，或正或斜，所发声音也是有轻有响，旁观众人均给扰得眼花撩乱，心神不定"NOR,
        YEL"一声「小心了！」，蓦然间$w"YEL"五体归一，并排向$n"YEL"撞去，势若五牛冲阵，威不可挡"NOR,
        HIB"只见$w"HIB"绕著$n"HIB"，上下翻飞，$w"HIB"跳跃灵动，呜呜响声不绝，掀的阵阵狂风有如刀割，似要把$n"HIB"从中劈开"NOR,
        HIR"突然，狂风乱起，激荡中那$w"HIR"相碰相撞，五轮归一，合并了向$n砸去"NOR,
        HIG"法轮在$n"HIG"身前环饶，猛地向$p"HIG"迎头击下，接着又飞来一轮，一抄一送，呜呜声响，兜向$n"HIG"$l"NOR,
        HIW"呼呼飞啸声中，那五只$w"HIW"或直飞、或斜飞、或回旋、或下坠、或上升，霎时间$n"HIW"的全部退路已被封死"NOR,
        HIC"猛地里$w"HIC"向$n"HIC"$l飞砸下，在$p"HIC"沉肩卸避之时，$w"HIC"又突然上飞击出，砸向$p"HIC"的$l"NOR,
        HIM"那$w"HIM"飞旋砸到，$n"HIM"却并不回头，听风辨器，一一挡开，但$w"HIM"便如长上了眼睛一般，竟然又旋飞到了$n"HIM"$l"NOR,
        HIG"随着森森慑人的厉吼，$w"HIG"锤蓦而急颤晃动，轮身嗡嗡震响，在不及眨眼的瞬息间，耀目的电光金蛇四射迸闪，飞掠周遭，迅捷无匹的击$n！"NOR,
        MAG"法轮再次合围，紫电精芒围著$n"MAG"的四周旋舞闪射，千百轮影幻映出一幅美丽而眩目的图案，这图案美极了，似是一片多角形的紫色雪晶体"NOR,
});
int valid_enable(string usage) { return usage == "hammer" || usage == "parry"; }
int valid_learn(object me)
{
        /*
        if( query("str", me)<32 )
                return notify_fail("你先天膂力不足，难以修炼日月轮法。\n");
        */

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("hammer", 1) < 100)
                return notify_fail("你的基本锤法不够，难以修炼日月轮法。\n");

        if ((int)me->query_skill("hammer", 1) < (int)me->query_skill("riyue-lun", 1))
                return notify_fail("你的基本锤法水平有限，无法领会更高深的日月轮法。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "hammer" )
                return notify_fail("你使用的武器不对。\n");
        if( query("qi", me)<50 || query("neili", me)<50 )
                return notify_fail("你的内力或气不够,练不了日月轮法。\n");
        me->receive_damage("qi", 40);
        addn("neili", -40, me);
        return 1;
}
/*
mixed hit_ob(object me, object victim, int damage_bonus)
{
        object my_w, victim_w;
        object piece;
        victim_w=query_temp("weapon", victim);
        my_w=query_temp("weapon", victim);

//      if( me->query("dex") < 20 || me->query("str") < 20 )

        if( query_temp("weapon", victim) || query_temp("secondary_weapon", victim) )
        {
                if( (int)(me->query_skill("riyue-lun", 1)) < 20 )
                        return HIW"一阵兵刃相撞的声音过后，对方兵器居然完好无损。\n"NOR;
                if( random(query_temp("apply/damage", victim))<random(me->query_skill("riyue-lun",1)/3) )
                {
                        if( objectp(my_w=query_temp("weapon", me)) &&
                                (query("id", my_w) == "falun"
                                   || query("id", my_w) == "yinlun"
                                    || query("id", my_w) == "jinlun" )
                                    && query("ownmake", my_w) != 1 )
                        {
                                seteuid(getuid());
                                piece = new("/clone/misc/piece");
                                piece->set_name(query("name", victim_w)+"的碎片",({query("id", victim_w),"piece"}));
                                piece->move(environment(victim));
                                set("long", "一堆破碎物事，好象是兵器碎片。\n", piece);
                                destruct(victim_w);
                                return HIB "你听到「叮当」一声兵刃破碎的声音，兵器碎片溅了一地！\n" NOR;
                        }
                        else return HIR"可惜你没用法轮，没法砸碎对方兵器！\n"NOR;
                }
        }
}
*/
mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon, weapon1;
        weapon=query_temp("weapon", me);
        weapon1=query_temp("weapon", victim);

        if (weapon && weapon1
        &&  me->query_skill("riyue-lun",1)>150 && query("jiali", me )
        &&  query("neili", me)>1000
        // &&  random(10) >= 5
        &&  query("skill_type", weapon) == "hammer"
        &&  me->query_skill_mapped("parry") == "riyue-lun")
        {
                message_combatd(HIW"$N手臂暴长，施展「锁」字诀，"+weapon->name()+
                                HIW"探出，嚓的一声锁住了$n"+weapon1->name()+HIW"。\n"NOR,
                                me, victim);

                if (random(me->query_str()) > victim->query_str())
                {
                        addn("neili", -100, me);
                        message_combatd(HIG+query("name", me)+"运劲回拉，$n臂骨喀的一声，险些就被拉断，剧痛之下手一松，"+
                                        weapon1->name()+HIG"被夺了过去！\n"NOR, me, victim);
                        weapon1->unequip();
                        weapon1->move(me);
                } else
                if (random(me->query_str()) > victim->query_str() / 2)
                {
                        addn("neili", -50, me);
                        message_combatd(HIG+query("name", me)+"运劲回拉，$N被带得踉跄几步，但觉虎口剧痛，"+
                                        weapon1->name()+HIG"脱手飞出！\n"NOR, victim);
                        weapon1->unequip();
                        weapon1->move(environment(victim));
                } else
                if( query_temp("shield", victim) )
                {
                        addn("neili", -50, me);
                        message_combatd(HIY"$N借势前冲，"+weapon1->name()+HIY"直刺过去，但被"+
                                        query("name", victim)+"护体真气荡得滑了开去。\n"NOR,victim);
                }

                else message_combatd(HIY"$N借势前冲，"+weapon->name()+HIY"直刺"+query("name", victim)+"，"+
                                        query("name", victim)+"变招奇快，"+weapon->name()+HIY"一抖松脱，纵身退了开去。\n"NOR,
                                        victim);
        }
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 20;
        int d_e2 = 40;
        int p_e1 = -40;
        int p_e2 = -20;
        int f_e1 = 300;
        int f_e2 = 400;
        int m_e1 = 100;
        int m_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);
        string str, message;
        if (weapon)
        {
                if( query("id", weapon) == "jin lun" )
                        str = "金轮";
                else if( query("id", weapon) == "yin lun" )
                        str = "银轮";
                else if( query("id", weapon) == "fa lun" )
                        str = "法轮";
                else str = weapon->name();
                message = msg[random(sizeof(msg))];
                message = replace_string(message, "$w", str);
                switch(str)
                {
                case "金轮" :
                        message = HIY+message+NOR; break;
                case "银轮" :
                        message = HIW+message+NOR; break;
                case "法轮" :
                        message = HIC+message+NOR; break;
                default : break;
                }
                return ([
                        "action" : message,
                        "damage" : 300,
                        "damage_type" : random(2)?"砸伤":"瘀伤",
                        "dodge" : -100,
                        "parry" : -100,
                        "attack": 200,
                ]);
        }
        lvl = (int) me->query_skill("riyue-lun", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 获得招数序号上限 */
                        break;
                }
        seq = random(seq);       /* 选择出手招数序号 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : "挫伤",
        ]);
}
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"riyue-lun/" + action;
}

int help(object me)
{
        write(HIC"\n日月轮法："NOR"\n");
        write(@HELP

    日月轮法为金轮法王的武功，是雪山寺极为霸道的功夫。

        学习要求：
                龙相般若功20级
                内力100
HELP
        );
        return 1;
}
