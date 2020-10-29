// quanzhen-jianfa 全真剑法

inherit SKILL;

mapping *action = ({
([      "action" : "$N贴地斜飞，一招「雁行斜击」，尚未落地，$w已指向$n的后心",
        "force" : 120,
        "dodge" : 20,
        "damage" : 25,
        "lvl" : 0,
        "damage_type" : "刺伤"
]),
([      "action" : "$N小步连跳，左手剑诀，右手$w使一式「浪迹天涯」直攻$n的左肋",
        "force" : 140,
        "dodge" : 15,
        "damage" : 30,
        "lvl" : 0,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招「花前月下」，模拟冰轮横空，清光铺地之光景，自上而下搏击",
        "force" : 170,
        "dodge" : 15,
        "damage" : 40,
        "lvl" : 9,
        "damage_type" : "刺伤"
]),
([      "action" : "$N剑柄提起，剑尖下指，一招「清饮小酌」，犹如提壶斟酒扫$n的下盘",
        "force" : 190,
        "dodge" : 10,
        "damage" : 50,
        "lvl" : 19,
        "damage_type" : "刺伤"
]),
([      "action" : "$N使出「抚琴按箫」，$w提至唇边，如同清音出箫，剑掌直出，划向$n的$l",
        "force" : 240,
        "dodge" : 10,
        "damage" : 60,
        "lvl" : 29,
        "damage_type" : "刺伤"
]),
([      "action" : "$N$w直截进击，自左而右，横扫数尺，一式「横行漠北」，迅疾逼向$n的肩头",
        "force" : 280,
        "dodge" : 5,
        "damage" : 70,
        "lvl" : 39,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招「举案齐眉」，左手捏剑诀，跃步落地，右手$w斜刺$n的左腰",
        "force" : 300,
        "dodge" : 5,
        "damage" : 80,
        "lvl" : 59,
        "damage_type" : "刺伤"
]),
([      "action" : "$N左掌前挥，右手扬剑跟随，一招「推窗望月」，身形前扬，往$n的$l杀至",
        "force" : 330,
        "dodge" : -5,
        "damage" : 90,
        "lvl" : 79,
        "damage_type" : "刺伤"
]),
([  "action" : "$N一招「分花拂柳」，$w似左实有右，似右实左，虚实莫辩，点向$n的腹部",
        "force" : 380,
        "dodge" : -5,
        "damage" : 115,
        "lvl" : 99,
        "damage_type" : "刺伤"
]),
([  "action" : "$N一招「锦笔生花」，英姿勃发，$w舞出数点寒心，若梅桃盛开，点向$n的$l",
        "force" : 380,
        "dodge" : -5,
        "damage" : 115,
        "lvl" : 99,
        "damage_type" : "刺伤"
]),
});


int valid_enable(string usage) { return (usage == "club") || (usage == "parry"); } 



int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的内力不够。\n");
        return 1;
        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的内功火候不到。\n");
}

mapping query_action(object me, object weapon)
{
        int i, level;
            level   = (int) me->query_skill("quanzhen-jianfa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
        if( query("jingli", me)<50 )
                return notify_fail("你的精力不够练全真剑法。\n");
        addn("jingli", -30, me);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"quanzhen-jianfa/" + action;
}