// fuqi-daofa.c　夫妻刀法
// By Alf, Last Update 2001.05

//　女貌郎才珠万斛　天教丽质为眷属　碧箫声里双鸣凤　清风引佩下瑶台
//　刀光掩映孔雀屏　明月照妆成金屋　喜结丝罗在乔木　千金一刻庆良宵

inherit SKILL;

mapping *action = ({
([  "action" : "$N轻轻一笑，手中$w斜指，一招「女貌郎才珠万斛」，反身撩向$n的$l",
    "force" : 120,
    "dodge" : -10,
    "lvl" : 0,
    "skill_name" : "女貌郎才珠万斛",
    "damage_type" : "割伤"
]),
([  "action" : "$N面带微笑，一招「天教丽质为眷属」，$w一提一收，平刃挥向$n的颈部",
    "force" : 130,
    "dodge" : -10,
    "damage" : 5,
    "lvl" : 8,
    "skill_name" : "天教丽质为眷属",
    "damage_type" : "割伤"
]),
([  "action" : "$N展颜微笑，$w刀锋左右开阖，一招「碧箫声里双鸣凤」，拦腰斩向$n",
    "force" : 140,
    "dodge" : -5,
    "damage" : 15,
    "lvl" : 16,
    "skill_name" : "碧箫声里双鸣凤",
    "damage_type" : "割伤"
]),
([  "action" : "$N使一招「清风引佩下瑶台」，$w自上而下划出一个大弧，笔直劈向$n",
    "force" : 160,
    "dodge" : 5,
    "damage" : 25,
    "lvl" : 24,
    "skill_name" : "清风引佩下瑶台",
    "damage_type" : "割伤"
]),
([  "action" : "$N手中$w一沉，一招「刀光掩映孔雀屏」，双手持刃反切，砍向$n胸口",
    "force" : 180,
    "dodge" : 10,
    "damage" : 30,
    "lvl" : 33,
    "skill_name" : "刀光掩映孔雀屏",
    "damage_type" : "割伤"
]),
([  "action" : "$N一招「明月照妆成金屋」，手中$w上劈下撩，左挡右开，齐齐罩向$n",
    "force" : 210,
    "dodge" : 15,
    "damage" : 35,
    "lvl" : 42,
    "skill_name" : "明月照妆成金屋",
    "damage_type" : "割伤"
]),
([  "action" : "$N跃步落地，$w顺势送出，一招「喜结丝罗在乔木」，斜斜劈向$n的$l",
    "force" : 240,
    "dodge" : 5,
    "damage" : 50,
    "lvl" : 51,
    "skill_name" : "喜结丝罗在乔木",
    "damage_type" : "割伤"
]),
([  "action" : "$N轻笑声中，「千金一刻庆良宵」使出，一片流光般的刀影涌向$n全身",
    "force" : 280,
    "dodge" : 20,
    "damage" : 60,
    "lvl" : 60,
    "skill_name" : "千金一刻庆良宵",
    "damage_type" : "割伤"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; } 

int valid_learn(object me)
{
    if( query("max_neili", me)<100 )
                return notify_fail("你的内力不够。\n");
    return 1;
}

string query_skill_name(int level)
{
    int i;
    for(i = sizeof(action)-1; i >= 0; i--)
    if(level >= action[i]["lvl"])
                return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level   = (int) me->query_skill("fuqi-daofa",1);
    for(i = sizeof(action); i > 0; i--)
    if(level > action[i-1]["lvl"])
                return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object weapon;

    if( !objectp(weapon=query_temp("weapon", me) )
     || query("skill_type", weapon) != "blade" )
      return notify_fail("你使用的武器不对。\n");
    if( query("qi", me)<50 )
      return notify_fail("你的体力不够练夫妻刀法。\n");
    me->receive_damage("qi", 25);
    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"fuqi-daofa/" + action;
}

