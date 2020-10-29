// 疯魔杖法
// by hunthu
//update by cool
#include <ansi.h>
inherit SKILL;
mapping *action = ({
([  "action": "$N斜举$w, 一招「秦王鞭石」，斜肩铲背砸向$n的$l",
        "force":120,
        "dodge": -8,
        "damage": 35,
        "lvl" : 0,
        "skill_name" : "秦王鞭石",
        "damage_type": "挫伤"
]),
([  "action": "$N一声大喝，使出一招「鲁达拔柳」, 手中$w自下而上扫向$n的$l",
        "force":200,
        "dodge": -5,
        "damage": 65,
        "lvl" : 39,
       "skill_name" : "鲁达拔柳",
       "damage_type": "挫伤"
]),

([  "action": "$N使出一招「霸王扛鼎」，将$w从肩头甩出砸向往$n的$l",
        "force":280,
        "dodge": -5,
                "damage": 85,
        "lvl" : 69,
        "skill_name" : "霸王扛鼎",
        "damage_type": "淤伤"
]),
([  "action": "$N身子一晃，一招「八仙醉打」，手中$w如狂风暴雨般向$n打出",
        "force":330,
        "dodge": -15,
                "damage": 100,
        "lvl" : 79,
        "skill_name" : "八仙醉打",
        "damage_type": "淤伤"
]),
([  "action": "$N一声咆哮，一招「长虹经天」, $w从手中掷出，飞向$n的$l",
        "force":380,
        "dodge": -10,
        "damage": 115,
        "lvl" : 89,
        "skill_name" : "长虹经天",
        "damage_type": "淤伤"
]),
});
string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;

        if (( (int)me->query_skill("staff", 1) >= 120 ) 
        &&        ( (int)me->query_skill("fengmo-zhang", 1) >= 150 )
        &&      ( (int)me->query_skill("force",1) >= 140 )
         && (query("neili", me) >= 500 )
        &&      ( random((int)me->query_str()) >= 30 )
                 && (query("shen", me)+10000<0)){
                return ([
                "action": RED"$N脸上突现煞气，举起$w，猛向$n後脑击落。这一杖出手又快又狠，竟是「伏魔杖法」中的毒招"NOR,
                "damage": (int)me->query_skill("fengmo-zhang",1)+(int)me->query_str(),
                "parry":(int)me->query_skill("dodge")/5,
                "force": 400,
                "damage_type": "内伤"]);
        }
        level   = (int) me->query_skill("fengmo-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }
int valid_learn(object me)
{
    if( query("max_neili", me)<200 )
        return notify_fail("你还是先集中精力修练内力吧。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;
        int lvl = me->query_skill("fengmo-zhang", 1);
        int i = sizeof(action);
        while (i--) if (lvl == action[i]["lvl"]) return 0;
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "staff" )
        return notify_fail("你手上的武器不能用来练疯魔杖法。\n");
        if( query("jingli", me)<60 )
        return notify_fail("你先歇口气再练吧。\n");
        me->receive_damage("jingli", 25);
        return 1;
}
