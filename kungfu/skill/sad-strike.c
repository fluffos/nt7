inherit SKILL;

#include <ansi.h>

mapping *action = ({
([      "action" : "$N一招「"HIW"杞人忧天"NOR"」抬头向天，浑若不见，呼的一掌"
                   "向自己头顶空空拍出，手掌斜下，掌力化成弧\n"
                   "形，四散落下拍向$n的$l",
        "force"  : 250,
        "attack" : 40,
        "dodge"  : 40,
        "damage" : 20,
        "lvl"    : 0,
        "skill_name" : "杞人忧天",
        "damage_type": "内伤"
]),
([      "action" : "$N一招「"HIG"无中生有"NOR"」手臂下垂，绝无半点防御姿式，"
                   "突然间手足齐动，左掌右袖、双足头锤、连得\n"
                   "胸背腰腹尽皆有招式发出撞向$n",
        "force"  : 260,
        "attack" : 45,
        "dodge"  : 45,
        "damage" : 25,
        "lvl"    : 10,
        "skill_name" : "无中生有",
        "damage_type": "瘀伤"
]),
([      "action" : "$N一招「"HIB"拖泥带水"NOR"」右手云袖飘动，宛若流水，左掌"
                   "却重滞之极，便似带着几千斤泥沙一般，左右\n"
                   "齐攻$n",
        "force"  : 280,
        "attack" : 50,
        "dodge"  : 50,
        "damage" : 30,
        "lvl"    : 20,
        "skill_name" : "拖泥带水",
        "damage_type": "内伤"
]),

([      "action" : "$N一招「"HIY"力不从心"NOR"」含胸收腹，头缓缓低下，脚步沉"
                   "重，右掌软绵绵的拍向$n的$l",
        "force"  : 300,
        "attack" : 55,
        "dodge"  : 55,
        "damage" : 35,
        "lvl"    : 40,
        "skill_name" : "力不从心",
        "damage_type": "瘀伤"
]),
([      "action" : "$N一招「"HIR"行尸走肉"NOR"」踢出一脚。这一脚发出时恍恍惚"
                   "惚，隐隐约约，若有若无的踢向$n",
        "force"  : 330,
        "attack" : 60,
        "dodge"  : 60,
        "damage" : 40,
        "lvl"    : 60,
        "skill_name" : "行尸走肉",
        "damage_type": "瘀伤"
]),
([      "action" : "$N双掌平托，一招「"HIM"庸人自扰"NOR"」没精打采的拍向$n的$l",
        "force"  : 360,
        "attack" : 70,
        "dodge"  : 65,
        "damage" : 45,
        "lvl"    : 80,
        "skill_name" : "庸人自扰",
        "damage_type": "瘀伤"
]),
([      "action" : "$N一招「"RED"倒行逆施"NOR"」突然纵起丈余，头下脚上，倒过"
                   "身子，一掌拍向$n的$l",
        "force"  : 390,
        "attack" : 80,
        "dodge"  : 70,
        "damage" : 50,
        "lvl"    : 100,
        "skill_name" : "倒行逆施",
        "damage_type": "瘀伤"
]),
([      "action" : "$N一招「"YEL"心惊肉跳"NOR"」凝目远眺，脚下虚浮，胸前门户"
                   "洞开，全身姿式与武学中各项大忌无不吻合",
        "force"  : 420,
        "attack" : 90,
        "dodge"  : 75,
        "damage" : 55,
        "lvl"    : 120,
        "skill_name" : "心惊肉跳",
        "damage_type": "内伤"
]),
([      "action" : "$N一招「"BLU"废寝忘食"NOR"」脚下虚浮，有如几天不吃不睡后"
                   "的脚步朗舱的袭到$n的身旁，左掌和右拳攻\n"
                   "向$n的$l",
        "force"  : 460,
        "attack" : 100,
        "dodge"  : 80,
        "damage" : 60,
        "lvl"    : 140,
        "skill_name" : "废寝忘食",
        "damage_type": "瘀伤"
]),
([      "action" : "$N一招「"HIC"徘徊空谷"NOR"」左攻右打，虚虚实实的攻向$n的$l",
        "force"  : 490,
        "attack" : 110,
        "dodge"  : 85,
        "damage" : 65,
        "lvl"    : 160,
        "skill_name" : "徘徊空谷",
        "damage_type": "瘀伤"
]),
([      "action" : "$N一招「"CYN"饮恨吞声"NOR"」左手做饮酒状，右掌斜斜劈向$n的$l",
        "force"  : 520,
        "attack" : 125,
        "dodge"  : 90,
        "damage" : 90,
        "lvl"    : 70,
        "skill_name" : "饮恨吞声",
        "damage_type": "瘀伤"
]),
([      "action" : "$N一招「"MAG"六神不安"NOR"」身如陀螺急转，展开轻功围着$n"
                   "快速游走，忽然飞身而起，拍向$n的$l",
        "force"  : 550,
        "attack" : 140,
        "dodge"  : 95,
        "damage" : 75,
        "lvl"    : 200,
        "skill_name" : "六神不安",
        "damage_type": "内伤"
]),
([      "action" : "$N一招「"WHT"穷途末路"NOR"」闪身到$n身旁，左掌举到胸前平"
                   "推而出，接着右掌斜斜劈向$n的$l",
        "force"  : 570,
        "attack" : 150,
        "dodge"  : 100,
        "damage" : 80,
        "lvl"    : 220,
        "skill_name" : "穷途末路",
        "damage_type": "瘀伤"
]),
([      "action" : "$N一招「"HIY"呆若木鸡"NOR"」双目直直的盯着$n，身体动也不"
                   "动一下的飞向$n",
        "force"  : 590,
        "attack" : 155,
        "dodge"  : 105,
        "damage" : 85,
        "lvl"    : 240,
        "skill_name" : "呆若木鸡",
        "damage_type": "内伤"
]),
([      "action" : "$N低头冥想，一招「"HIB"若有所失"NOR"」右掌向外平平推向$n"
                   "的$l",
        "force"  : 620,
        "attack" : 160,
        "dodge"  : 110,
        "damage" : 90,
        "lvl"    : 260,
        "skill_name" : "若有所失",
        "damage_type": "瘀伤"
]),
([      "action" : "$N一招「"HIB"四通八达"NOR"」双掌晃出千万掌影将$n笼罩在掌"
                   "力之下",
        "force"  : 650,
        "attack" : 165,
        "dodge"  : 115,
        "damage" : 95,
        "lvl"    : 280,
        "skill_name" : "四通八达",
        "damage_type": "内伤"
]),
([      "action" : "$N错步上前，一招「"HIB"鹿死谁手"NOR"」招招抢先，以快打慢，"
                   "一个转身已经转到了$n的身后，运指如风点\n"
                   "向$n的大椎穴",
        "force"  : 680,
        "attack" : 170,
        "dodge"  : 120,
        "damage" : 100,
        "lvl"    : 300,
        "skill_name" : "鹿死谁手",
        "damage_type": "内伤"
]),
});

int valid_enable(string usage) { return usage == "unarmed" || usage == "parry"; }

int valid_learn(object me)
{
        // 无天性限制 ---- 黯然销魂者，唯别而已矣

        if( query("gender", me) != "男性" )
                return notify_fail("你体会不到男人思念一个人的心情，无法领悟黯然销魂掌。\n");

        if( query("character", me) == "心狠手辣" )
                return notify_fail("你一心想杀尽敌人，结果没能进入黯然销魂的境界。\n");

        if( query("character", me) == "阴险奸诈" )
                return notify_fail("你一心想去害人，结果没能进入领悟黯然销魂的境界。\n");

        if( query("str", me)<28 )
                return notify_fail("你先天臂力不足，无法修炼黯然销魂掌。\n");

        if( query("int", me)<24 )
                return notify_fail("你先天悟性不足，无法修炼黯然销魂掌。\n");

        if ((int)me->query_str() < 45)
                return notify_fail("你的膂力太弱，无法练黯然销魂掌。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练黯然销魂掌必须空手。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的内力修为不足，无法练黯然销魂掌。\n");

        if (me->query_skill("force") < 320)
                return notify_fail("你内功修为不足，无法修炼黯然销魂掌。\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("你的基本拳脚不够娴熟，无法练黯然销魂掌。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("sad-strike", 1))
                return notify_fail("你的基本拳脚水平有限，无法领会更高深的黯然销魂掌。\n");

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
        int d_e1 = 10;
        int d_e2 = 30;
        int p_e1 = -45;
        int p_e2 = 25;
        int f_e1 = 300;
        int f_e2 = 400;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("sad-strike", 1);
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
                "damage_type" : random(2) ? "内伤" : "瘀伤",
        ]);
}

int practice_skill(object me)
{
        int cost;

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必须空手才能练习。\n");

        if( query("qi", me)<101 )
                return notify_fail("你的体力太低了。\n");

        cost = me->query_skill("sad-strike", 1) / 5 + 100;
        if( query("neili", me)<cost )
                return notify_fail("你的内力不够练黯然消魂掌。\n");

        me->receive_damage("qi", 100);
        addn("neili", -cost, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        string msg;
        mixed result;
        int j;

        j = me->query_skill("sad-strike", 1);
        if (damage_bonus < 50) return 0;

        if (random(20) >= 10 && ! victim->is_busy() && j > 140)
        {
                switch(random(3))
                {
                case 0 :
                        msg = YEL"$N抬头向天，浑若不见，呼的一掌向头顶空空拍出，手掌斜下，掌力化成弧形，四散落下！\n"NOR;
                        msg += HIR"结果$n被这一招「杞人忧天」带得别说挣扎，竟连站定脚步也是不能。\n"NOR;
                        victim->start_busy(2 + random(2));
                        break;
                case 1 :
                        msg = HIB"$N右手云袖飘动，宛若流水，左掌却重滞之极，便似带着几千斤泥沙一般！\n"NOR;
                        msg += HIR"结果$n被这一招「拖泥带水」带得犹如身陷洪涛巨浪，跌跌撞撞。\n"NOR;
                        victim->start_busy(3 + random(2));
                        break;
                case 2 :
                        msg = HIG"突然间$N手足齐动，左掌右袖、双足头锤、连得胸背腰腹尽皆有招式发出！\n"NOR;
                        msg += HIR"结果$n被这一招「无中生有」带得自身全然身不由主的境地。\n"NOR;
                        victim->start_busy(4 + random(2));
                        break;
                }
                return msg;
        } else
        {
                result = ([ "damage" : damage_bonus ]);
                result += ([ "msg" : HIR "只听到“哇”的一声，$n" HIR "喷出了一大口鲜血！\n" NOR]);

                return result;
        }

}

string perform_action_file(string action)
{
        return __DIR__"sad-strike/" + action;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( query_temp("weapon", me) )
                return 0;

        lvl = me->query_skill("sad-strike", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }
int help(object me)
{
        write(HIC"\n黯然销魂掌："NOR"\n");
        write(@HELP

    杨过自和小龙女在绝情谷断肠崖前分手，不久便由神雕带着在
海潮之中练功，数年之后，除了内功循序渐进之外，别的无可再练，
心中整日价思念小龙女，渐渐的形销骨立，了无生趣。一日在海滨
悄然良久，百无聊赖之中随意拳打脚踢，其时他内功火候已到，一
出手竟具极大威力，轻轻一掌，将海滩上一只大海龟的背壳打得粉
碎。他由此深思，创出了一套完整的掌法，出手与寻常武功大异，
厉害之处，全在内力，一共是一十七招。
    杨过生平受过不少武学名家的指点，自全真教学得玄门正宗内
功的口诀，自小龙女学得【玉女心经】，在古墓中见到【九阴真经
】，欧阳锋以蛤蟆功和逆转经脉，洪七公与黄蓉授以打狗棒法，黄
药师授以弹指神通和玉箫剑法，除了一阳指之外，东邪、西毒、北
丐、中神通的武学无所不窥，而古墓派的武学又于五大高人之外别
创蹊径，他依此融会贯通，卓然成家，创立此掌法。只因他单剩一
臂，是以不在招数变化取胜，反而故意与武学通理相反。将这套掌
法定名为“黯然销魂掌”，取的是江淹【别赋】中那一句“黯然销
魂者，唯别而已矣”之意。实饱含对小龙女的刻骨思念之情。

        学习要求：
                玉女心法100级
                内力1500
                只能向杨过学习
HELP
        );
        return 1;
}