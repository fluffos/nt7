#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action":"$N翻腕一振$w，一招「"+HIY"狮子摇头"NOR+"」，枪上红缨抖动，挽出斗大一个枪花，往$n$l直搠过去",
        "lvl" : 0,
        "skill_name" : "狮子摇头",
        "damage_type":  "刺伤"
]),
([      "action":"$N倒转$w，一招「"+HIY"白虹经天"NOR+"」，斜身移睬宫枪杆起处，圆圆一团红影，枪尖上一点寒光疾向$n刺来",
        "lvl" : 30,
        "skill_name" : "白虹经天",
        "damage_type":  "割伤"
]),
([      "action":"$N催动身法急走如飞，手中$w一抖，使出一招「"+HIY"朝天一柱香"NOR+"」，$w挺得笔直，迅捷无伦地刺向$n的$l",
        "lvl" : 60,
        "skill_name" : "朝天一柱香",
        "damage_type":  "割伤"
]),
([      "action":"$N挺起$w，一招「"+HIY"凤点头"NOR+"」，红缨抖动，$w幻出点点枪影，枪尖闪烁不定地往$n$l点到",
        "lvl" : 90,
        "skill_name" : "凤点头",
        "damage_type":  "刺伤"
]),
([      "action":"$N一招「"+HIY"春雷震怒"NOR+"」，刷刷刷连环三枪，急刺而至，朱缨乱摆，$w嗤嗤声响，颤成一个大红圈子，罩住了$n上下各路",
        "lvl" : 120,
        "skill_name" : "春雷震怒",
        "damage_type":  "割伤"
]),
([      "action":"$N突然大喝一声，双手抓住枪柄，劲力到处$w弯成弓形，突然一松手，电光一闪劈空刺向$n，好一招「"+HIY"灵蛇电闪"NOR+"」",
        "lvl" : 150,
        "skill_name" : "灵蛇电闪",
        "damage_type":  "刺伤"
]),
([      "action":"$N突然踏上一睬宫$w挺得笔直，使出一招「"+HIY"孤雁出群"NOR+"」，$w来势如风，凌厉无匹地向$n的$l刺去",
        "lvl" : 180,
        "skill_name" : "孤雁出群",
        "damage_type":  "刺伤"
]),
});

int valid_enable(string usage)
{
        if (query("quest/射雕英雄传/yangjiaqiang/pass", this_player()))
                 return usage == "spear" || usage == "parry";
}

int valid_learn(object me)
{
        if( me->query_skill("yangjia-qiang", 1) < 1 )
                return notify_fail("杨家枪只能从杨铁心处习到。\n");
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
        int i, j, level,lv2;
        level = me->query_skill("yangjia-qiang",1);
        lv2 = me->query_skill("spear", 1)/2;

        for(i = sizeof(action); i > 0; i--){
                if(level > action[i-1]["lvl"]){
                        j = NewRandom(i, 20, level/5);

                        if( query_temp("yjq/huima", me)){
                                return ([  
                                        "action":HIC+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIC), NOR, HIC)+NOR,
                                        "lvl" : action[j]["lvl"],
                                        "force" : 120 + random(250) + lv2/10,
                                        "dodge": random(20)- 5 +lv2/15,
                                        "damage": 60 + random(80) + random((level+lv2)/4),
                                        "parry": random(15)+lv2/10,
                                        "weapon" : random(2)?"枪气":"枪锋",
                                        "damage_type" : random(2)?"刺伤":"割伤",
                                ]);
                        }
                        if( query_temp("yjq/jifeng", me)){
                                return ([  
                                        "action":MAG+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"MAG), NOR, MAG)+NOR,
                                        "lvl" : action[j]["lvl"],
                                        "force" : 120 + random(250) + lv2/10,
                                        "dodge": random(20)- 5 +lv2/15,
                                        "damage": 70 + random(100) + random((level+lv2)/4),
                                        "parry": random(15)+lv2/10,
                                        "weapon" : random(2)?"枪气":"枪锋",
                                        "damage_type" : random(2)?"刺伤":"割伤",
                                ]);
                        }
                                                if( query_temp("yjq/qinghe", me)){
                                return ([  
                                        "action":HIG+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIG), NOR, HIG)+NOR,
                                        "lvl" : action[j]["lvl"],
                                        "force" : 120 + random(250) + lv2/10,
                                        "dodge": random(20)- 5 +lv2/15,
                                        "damage": 80 + random(100) + random((level+lv2)/5),
                                        "parry": random(15)+lv2/10,
                                        "weapon" : random(2)?"枪气":"枪锋",
                                        "damage_type" : random(2)?"刺伤":"割伤",
                                ]);
                        }
                        if( query_temp("yjq/shenwei", me)){
                                return ([  
                                        "action":HIR+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIR), NOR, HIR)+NOR,
                                        "lvl" : action[j]["lvl"],
                                        "force" : 120 + random(250) + lv2/10,
                                        "dodge": random(20)- 5 +lv2/15,
                                        "damage": 80 + random(100) + random((level+lv2)/5),
                                        "parry": random(15)+lv2/10,
                                        "weapon" : random(2)?"枪气":"枪锋",
                                        "damage_type" : random(2)?"刺伤":"割伤",
                                ]);
                        }
                        return ([
                                "action": action[j]["action"],
                                "force" : 100 +random(250),
                                "dodge": random(20)-10,
                                "parry": random(10),
                                "damage": 80 +random(80),
                                "lvl": action[j]["lvl"],
                                "damage_type": action[j]["damage_type"],
                        ]);
                }
        }
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "spear" )
                return notify_fail("你使用的武器不对。\n");
        if( query("jingli", me)<50 )
                return notify_fail("你的体力不够练杨家枪。\n");
        me->receive_damage("jingli", 20);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yangjia-qiang/" + action;
}


mixed hit_ob(object me, object target)
{
        int lv = me->query_skill("yangjia-qiang");

        if( random(5)>3 && lv>250 && !query_temp("yjq/hmq", me) )
          {
                message_vision(YEL"$N大喝一声，双手抓住枪柄，斗然间拧腰纵臂，回身出枪，直刺$n面门，这一枪正是杨家枪法的“回马枪”" NOR,me,target);
                addn_temp("apply/attack", me->query_skill("yangjia-qiang",1)/3, me);
                set_temp("yjq/hmq", 1, me);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),random(4)?1:3);
                addn_temp("apply/attack", -me->query_skill("yangjia-qiang",1)/3, me);
                me->delte_temp("yjq/hmq");
         }
     
}

