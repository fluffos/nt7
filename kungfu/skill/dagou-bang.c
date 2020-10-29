// dagou-bang.c 打狗棒法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action": "$N使出一招"HIG"「棒打双犬」"NOR"，手中$w化作两道青光砸向$n的$l",
        "lvl"        : 10,
        "skill_name" : "棒打双犬"
]),
([      "action": "$N手中$w左右晃动，一招"HIG"「拨草寻蛇」"NOR"向$n的$l攻去",
        "lvl"        : 20,
        "skill_name" : "拨草寻蛇"
]),
([      "action": "$N举起$w，居高临下使一招"HIG"「打草惊蛇」"NOR"敲向$n的$l",
        "lvl"        : 30,
        "skill_name" : "打草惊蛇"
]),
([      "action": "$N施出"HIG"「拨狗朝天」"NOR"，$w由下往上向$n撩去",
        "lvl"        : 40,
        "skill_name" : "拨狗朝天"
]),
([      "action":"$N眼中射出一道青芒，手中绿玉棒使出"HIR"「天下无狗」"NOR"，劈天盖地劈落",
        "lvl"        : 50,
        "skill_name" : "天下无狗"
]),
});

int valid_enable(string usage)
{
        return usage == "staff" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("dex", me)<26 )
                return notify_fail("你的先天身法太差，无法学习打狗棒法。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力修为不足，无法学习打狗棒法。\n");

        if ((int)me->query_skill("staff", 1) < 100)
                return notify_fail("你的基本杖法不够，无法学习打狗棒法。\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("dagou-bang", 1))
                return notify_fail("你的基本杖法水平有限，无法领会更高深的打狗棒法。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的体力不够练打狗棒法。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够练打狗棒法。\n");

        me->receive_damage("qi", 75);
        addn("neili", -80, me);
        return 1;
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
        int d_e1 = -60;
        int d_e2 = -30;
        int p_e1 = -10;
        int p_e2 = 10;
        int f_e1 = 300;
        int f_e2 = 400;
        int m_e1 = 100;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("dagou-bang", 1);
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

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int) me->query_skill("dagou-bang", 1) < 100
            || !query_temp("feng_zijue", me )
            || !(weapon=query_temp("weapon", me) )
            || ! living(me)
            || query("skill_type", weapon) != "staff" )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("dagou-bang", 1);

        if (ap / 2 + random(ap) < dp * 3 / 4)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIG "巧妙的施展打狗棒「" HIY "封"
                                            HIG "」字诀，手中" + weapon->name() + HIG
                                            "左封右闭，使得$N" HIG "的攻势全然落空。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIG "$n" HIG "急转手中" + weapon->name() +
                                            HIG "，打狗棒「" HIY "封" HIG "」字诀发挥"
                                            "得淋漓尽致，顿将$N" HIG "的招式驱于无形。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(2))
                {
                case 0:
                        result = HIY "$n" HIY "蓦地施展出打狗棒「封」字"
                                 "诀，可是$N" HIY "理也不理，当即挥招直"
                                 "入，进袭$n" HIY "。\n" NOR;
                        break;
                default:
                        result = HIY "$n" HIY "急转手中" + weapon->name() +
                                 HIY "，左封右闭，然而$N" HIY "却是精演"
                                 "天数，丝毫不受$n" HIY "的迷惑。\n"  NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

mixed hit_ob(object me, object victim, int damage)
{
//      string msg;
        int ap, dp, zhencost;
        string result;
        object weapon;
        int fmsk = me->query_skill("bixue-danxin", 1);

        if (random(fmsk) >= random(600))
                damage += fmsk / 2 + random(fmsk / 2);

        if( !objectp(weapon=query_temp("weapon", me)) )
                return 0;

        zhencost = sqrt(weapon->weight() / 10) + 10;
        if( query("neili", me)<zhencost || query("jing", me)<zhencost )
                return 0;

        ap = me->query_skill("stick", 1) / 2 +
             me->query_skill("dagou-bang", 1);

        dp = victim->query_skill("dodge", 1) / 2 +
              victim->query_skill("parry", 1) / 4;
        dp += victim->query_skill("martial-cognize", 1);



        if (random(ap+dp) > ap)
        {
                result=HIG"突然青光闪动，棒招来势神妙无方，"+query("name", weapon)+HIG"击中了$n。\n"NOR;
                damage=query("weapon_prop/damage", weapon)*3;
                if (! victim->is_busy())
                        victim->start_busy(1 + random(3));
                addn("neili", -zhencost, me);
                addn("jing", -zhencost, me);
                return ([ "msg" : result, "damage" : damage ]);
        }
        else if (random(ap + 2 * dp) > ap)
        {
                result = HIG "$N猛地递出一招，这一棒迅捷无伦，直取$n眉心，$p「啊」的一声，连退出数尺！\n" NOR;
                damage=query("weapon_prop/damage", weapon)*2;
                if (! victim->is_busy())
                        victim->start_busy(1 + random(2));
                addn("neili", -zhencost, me);
                addn("jing", -zhencost, me);
                return ([ "msg" : result, "damage" : damage ]);
        }
        else
        {
                result = weapon->name()+ HIG "幌动，霎眼之间竟已转到$n身后，拍的一声，在$p臀上抽了一下。！\n" NOR;
                damage=query("weapon_prop/damage", weapon);
                if (! victim->is_busy())
                        victim->start_busy(1+random(1));
                addn("neili", -zhencost, me);
                addn("jing", -zhencost, me);
                return ([ "msg" : result, "damage" : damage ]);
        }
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 5; }
int power_point() { return 1.0; }
int query_effect_parry(object attacker, object me)
{
        int lvl;
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "staff" )
                return 0;

        lvl = me->query_skill("dagou-bang", 1);
        if (lvl < 80)  return 50;
        if (lvl < 200) return 100;
        if (lvl < 280) return 160;
        if (lvl < 350) return 200;
        return 240;
}

string perform_action_file(string action)
{
        return __DIR__"dagou-bang/" + action;
}

int help(object me)
{
        write(HIC"\n打狗棒法："NOR"\n");
        write(@HELP

    三十六路打狗棒法是丐帮开帮祖师爷所创，历来是前任帮主传
后任帮主，决不传给第二个人。丐帮第三任帮主的武功尤胜开帮祖
师，他在这路棒法中更加入无数奥妙变化。数百年来，丐帮逢到危
难关头，帮主亲自出马，往往便仗这打狗棒法除奸杀敌，镇慑群邪。
    打狗棒法名字虽然陋俗，但变化精微，招术奇妙，实是古往今
来武学中第一等特异的功夫，卓然自成一家，与各门派的功夫均无
牵涉。单学招数，若是不明『绊、劈、缠、戳、挑、引、封、转』
八字口诀，那是一点无用。每句口诀，须与每个招数相配，威力无
俦。为丐帮帮主历代相传的镇帮之宝。

        学习要求：
                混天气功50级
                内力200
HELP
        );
        return 1;
}