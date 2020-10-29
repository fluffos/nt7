#include <ansi.h>
#include <combat.h>
inherit SKILL;
mapping *action = ({
([  "action":"$N将$w扣在拇指上用力一弹，一招「"+MAG+"飞花逐蝶"+NOR+"」$w夹杂着丝丝劲风射向$n的$l",
    "force" : 180,
    "lvl" : 0,
    "skill_name" : MAG "飞花逐蝶" NOR,
    "damage_type":"刺伤",
    "post_action":  (: call_other, WEAPON_D, "throw_weapon" :),
 ]),
([  "action":"$N左手一扬一招「"+HIW+"雪花翩翩"+NOR+"」$w犹如雪花，似缓实速射向$n的$l",
    "force" : 180,
    "lvl" : 40,
    "skill_name" : HIW "雪花翩翩"NOR,
    "damage_type":"刺伤",
    "post_action":  (: call_other, WEAPON_D, "throw_weapon" :),
]),
([  "action":"$N大喝一声一招「"+BLU+"乾坤一掷"+NOR+"」手中$w突然急射而出",
    "force" : 180,
    "lvl" : 80,
    "skill_name" : BLU "乾坤一掷" NOR,
    "damage_type":"刺伤",
    "post_action":  (: call_other, WEAPON_D, "throw_weapon" :),
]),
([  "action":"$N身形加快一招「"+RED+"薰容逐电"+NOR+"」$w闪电一般射向$n的$l",
    "force" : 180,
    "lvl" : 120,
    "skill_name" : RED "薰容逐电" NOR,
    "damage_type":"刺伤",
    "post_action":  (: call_other, WEAPON_D, "throw_weapon" :),
]),
([  "action":"$N突然身形一跃，手一扬一招「"+YEL+"流荧飞逝"+NOR+"」,$w闪电一般射向$n的$l",
    "force" : 180,
    "lvl" : 160,
    "skill_name" : YEL "流荧飞逝" NOR,
    "damage_type":"刺伤",
    "post_action":  (: call_other, WEAPON_D, "throw_weapon" :),
]),
([  "action":"$N不快不慢，一招「"+HIW+"流星逐月"+NOR+"」,$w在半空中划出一道圆弧射向$n的$l",
    "force" : 180,
    "lvl" : 200,
    "skill_name" : HIW "流星逐月" NOR,
    "damage_type":"刺伤",
    "post_action":  (: call_other, WEAPON_D, "throw_weapon" :),
]),
});
int valid_enable(string usage) { return usage == "throwing"; }
int practice_level(){   return 200;  }
int valid_learn(object me)
{
      if (me->query_skill("throwing",1) <= me->query_skill("wmantianhuayu",1))
      return notify_fail("你的基础不够，无法领会更高深的技巧！\n");
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
    mapping a_action;
    int i, level;
    
    level   = (int) me->query_skill("wmantianhuayu",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"]){
                        a_action = action[NewRandom(i, 20, level/5)];
                        break;
                }
    a_action["dodge"]  = 0-level/3;
    a_action["damage"] = level+random(level);
    if( query_temp("wmantianhuayu", me)>0 )
        return (["action":BOLD"一"+query("unit", weapon)+"$w"+BOLD+"射向$n"+BOLD+"的$l"NOR,
                 "dodge": -3*random(level),
                 "damage": level,
                 "damage_type":"刺伤",
                 "post_action":  (: call_other, WEAPON_D, "throw_weapon" :),
                ]);
    return a_action;

}

int practice_skill(object me)
{
    object ob;
    if( query("qi", me)<30
     || query("neili", me)<35 )
        return notify_fail("你的内力或气不够，没有办法练习漫天花雨。\n");
    if( !objectp(ob=query_temp("weapon", me) )
     || query("skill_type", ob) != "throwing" )
    if( !objectp(ob=query_temp("secondary_weapon", me) )
     || query("skill_type", ob) != "throwing" )
        return notify_fail("你装备的武器不对。\n");
    me->receive_damage("qi", 30);
    addn("force", -20, me);
    addn_temp("pratice_throwing", 1, me);
    if( query_temp("pratice_throwing", me)>me->query_skill("wmantianhuayu",1)/20){
           if( (int)ob->query_amount()==1 ) {
                   ob->unequip();
                   tell_object(me,BOLD"\n你的"+query("name", ob)+"用完了！\n\n"+NOR);
           }
           ob->add_amount(-1);
           delete_temp("pratice_throwing", me);
    }
    write("你按著所学练了一遍漫天花雨。\n");
    return 1;
}

void do_interlink(object me, object victim)
{
    int skill,i,j;
    object*enemy,weapon=query_temp("weapon", me);
    string all_enemy;
    
    if (!weapon) return;
    skill=me->query_skill("wmantianhuayu", 1);
    if (random(skill)>250){
        enemy=me->query_enemy();
        if (!sizeof(enemy)) return;
        if( sizeof(enemy) == 1 && query("eff_qi", enemy[i])<0)return ;
        all_enemy=enemy[0]->name();
        for (i=1;i<sizeof(enemy);i++)
            all_enemy+=("、"+enemy[i]->name());
        message_vision(BOLD+"$N纵身跃起，衣袖一挥，几"+query("unit", weapon)+weapon->name()+"同时射向"+all_enemy+"。\n\n"NOR,me);
        set_temp("wmantianhuayu", 1, me);
        for (i=0;i<sizeof(enemy);i++){
            for (j=0;j<(skill/(60*sizeof(enemy)));j++)
                if( (me->is_fighting(enemy[i]) || enemy[i]->is_fighting(me)) && query("eff_qi", enemy[i])>0){
                    if (environment(me) == environment(enemy[i]))
                     {
                        COMBAT_D->do_attack(me,enemy[i],query_temp("weapon", me),TYPE_QUICK);
                     }
                }else break;
        }
    delete_temp("wmantianhuayu", me);
    }
}
