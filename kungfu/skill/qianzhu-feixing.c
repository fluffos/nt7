//duoming-jinhua 夺命金花
// 1997-2-14

inherit SKILL;

string  *msg = ({
"$N一式「变幻多端」，忽听得飕飕两声，黄光闪动，$w向$n的$l射出",
"$w倏左倏右，四面八方的罩向$n，却是$N以一式「倏左倏右」向$n发出八枚$w",
"$N低哼一声，一式「仙女散花」，的把$w向$n撒出，共有四四一十六之多",
"$n只听得飕飕声响，却是$N一招「满天星雨」，十多枚$w向$n各大穴飞去",
"突然黄光一闪，$N一式「千里追魂」，三枚$w向$n的胸口要害打去",
"$N一式「回头望月」，突然反手掷出三枚$w，飞向$n的后脑",
"$N一招「闪电风雷」，五枚$w连续飞射，破风声劲急，快得$n不能看清形影",
"$N一招「金花夺命」，全身飞扑而进，左手飞扬，四枚$w射向$n和胸部",
"$N飞身而起，一招「梅花顿现」，$w一枚枚的从$N手中飞出，杂杂梅花射向$n"
});

int valid_enable(string usage)
{
        return usage == "throwing" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        return ([
                "action":msg[random(sizeof(msg))],
                "damage":(random(3)+1)*50,
                "damage_type":random(2)?"刺伤":"割伤",
                "dodge":random(30),
                "force":random(200)+100,
                "post_action":
                  (: call_other, WEAPON_D, "throw_weapon" :)
                ]);
}
int practice_skill(object me)
{
       object weapon;
       if( !objectp(weapon=query_temp("weapon", me) )
        || query("skill_type", weapon) != "throwing" )
               return notify_fail("你使用的武器不对。\n");
       if( query("jingli", me)<50 )
               return notify_fail("你的体力不够练夺命金花。\n");
       me->receive_damage("jingli", 30);
       return 1;
}

int valid_learn(object me)
{
       if( query("max_neili", me)<500 )
               return notify_fail("你的内力不够。\n");
       if ((int)me->query_skill("shenghuo-shengong", 1) < 50)
               return notify_fail("你的圣火神功火候太浅。\n");
               return 1;
}
string perform_action_file(string action)
{
       return __DIR__"duoming-jinhua/" + action;
}
