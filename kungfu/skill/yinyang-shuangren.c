//yinyang-shuangren.c  阴阳双刃
//Jiuer /9/30/2001      绝情谷庄主 独家功夫

inherit SKILL;

mapping *action = ({
([        "action" : "$N口中大喊一声「看招」，一式「幽谷传声」，手中的$w划了个圆圈直绕到$n的$l",
        "force" : 100,
        "dodge" : -5,
        "damage" : 15,
        "lvl" : 0,
        "skill_name" : "幽谷传声",
        "damage_type" : "刺伤"
]),
([      "action" : "$N手中$w招势越划越大，一招「划圈逼敌」，$w已绕到$n的$l，直逼下来",
        "force" : 120,
        "dodge" : -5,
        "damage" : 25,
        "lvl" : 5,
                "skill_name" : "划圈逼敌",
        "damage_type" : "刺伤",
]),
([      "action" : "$N一招「漫天飞舞」，右手中的$w向前弯成弧形刺向$n的$l",
        "force" : 140,
        "dodge" : -10,
        "damage" : 55,
        "lvl" : 15,
                "skill_name" : "漫天飞舞",
        "damage_type" : "刺伤",
]),
([      "action" : "$N一式「莲花吐蕊」，手中$w斗地弯弯的绕着刺向$n的$l",
        "force" : 160,
        "dodge" : -10,
        "damage" : 85,
        "lvl" : 30,
                "skill_name" : "莲花吐蕊",
        "damage_type" : "割伤",
]),
([      "action" : "$N$w胸前一横，一招「僮子拜佛」，$w横斫，斜刺$n",
        "force" : 180,
        "dodge" : -15,
        "damage" : 120,
        "lvl" : 45,
                "skill_name" : "僮子拜佛",
        "damage_type" : "割伤",
]),
([          "action" : "$N向后一闪，一招「阴阳倒乱」，右手$w左击，立时剑法变刀法，$w随即刺出",
            "force" : 200,
            "dodge" : -15,
            "damage" : 100,
            "lvl" : 60,
                "skill_name" : "阴阳倒乱",
            "damage_type" : "刺伤",
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        mapping a_action;
        int i, level;
        level = (int) me->query_skill("yinyang-shuangren",1);
        for( i = sizeof(action); i > 0; i-- )
                if( level > action[i-1]["lvl"] )
                {
                        a_action = action[NewRandom(i, 20, level/5)];
                        break;
                }
        a_action["dodge"] -= level / 10;
        a_action["parry"] = -level / 10;
        a_action["force"] += level / 10;
        a_action["damage"] += level / 10;
        return a_action;

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
        if( query("jingli", me)<30 )
                return notify_fail("你的精力不够练阴阳双刃。\n");
        me->receive_damage("jingli", 20);
        return 1;
}
