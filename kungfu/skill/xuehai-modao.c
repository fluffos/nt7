// 血海魔刀
#include <ansi.h>
inherit SKILL;
#include "/kungfu/skill/eff_msg.h";;

mapping *action = ({
([      "action" : CYN"$N一招「"HIR"磨牙吮血"CYN"」，将$w"CYN"衔在嘴里，等$n走近了，突然间左手抓住刀柄，顺手一挥，砍向$p$l"NOR,
        "skill_name" : "磨牙吮血",
        "force" : 200,
        "dodge" : 15,
        "lvl" : 0,
        "damage" : 150,
        "damage_type" : "割伤",
]),
([      "action" : CYN"$N嘿嘿一笑，一式「"MAG"批纸削腐"CYN"」，一刀横削过去，$n只觉眼前红光闪动，$l上微微一凉"NOR,
        "skill_name" : "批纸削腐",
        "force" : 240,
        "dodge" : 25,
        "lvl" : 20,
        "damage" : 175,
        "damage_type" : "割伤",
]),
([      "action" : CYN"$N衔$w"CYN"在口，空手在$n身旁穿来插去，蓦地里右手从口中抽出刀来，「"HIR"血海茫茫"CYN"」一挥之下，刀锋直劈$p$l"NOR,
        "skill_name" : "血海茫茫",
        "force" : 280,
        "dodge" : 30,
        "lvl" : 30,
        "damage" : 160,
        "damage_type" : "割伤",
]),
([      "action" : CYN"$N嘿嘿冷笑声中，一招「"HIR"血洗天河"CYN"」，突见那$w"HIR"红影"CYN"闪闪，迎头弯转，竟如一根软带一般曲了下来，刀头削向$n$l"NOR,
        "skill_name" : "血洗天河",
        "force" : 320,
        "dodge" : 55,
        "lvl" : 50,
        "damage" : 190,
        "damage_type" : "割伤",
]),
([      "action" : CYN"$N身子向前一探，一招「"HIR"血蛇逐电"CYN"」，$w"CYN"颤动，刀刃便如一条赤练蛇一般，迅速无伦地在$n身上爬行而过，随即收刀入鞘，哈哈大笑"NOR,
        "skill_name" : "血蛇逐电",
        "force" : 350,
        "dodge" : 75,
        "lvl" : 70,
        "damage" : 200,
        "damage_type" : "割伤",
]),
([      "action" : CYN"$N低吼一声，凛然生威，将手中$w"CYN"刀柄反拿，一式「"HIR"血痕累累"CYN"」，卷起片片刀风斩向$n的$l"NOR,
        "skill_name" : "血痕累累",
        "force" : 380,
        "dodge" : 60,
        "lvl" : 90,
        "damage" : 260,
        "damage_type" : "割伤",
]),
([      "action" : CYN"$N气透刀尖，卷起刺骨寒风，一招「"BLU"血风刺骨"CYN"」向前直劈而下，一道红光从上至下剖向$n的$l"NOR,
        "skill_name" : "血风刺骨",
        "force" : 500,
        "dodge" : 55,
        "lvl" : 100,
        "damage" : 380,
        "damage_type" : "割伤",
]),
([      "action" : CYN"$N一式「"HIR"血雨空鸣"CYN"」，一口$w"CYN"越使越快，一团团红影笼罩了全身，向$n连砍数刀，都是只攻不守，极其凌厉的招数"NOR,
        "skill_name" : "血雨空鸣",
        "force" : 620,
        "dodge" : 10,
        "lvl" : 120,
        "damage" : 320,
        "damage_type" : "割伤",
]),
([      "action" : CYN"$N略略侧身，一招「"MAG"斩头式"CYN"」反手从背后横劈出一刀，直奔$n的项颈。\n  "NOR,
        "skill_name" : "斩头式",
        "force" : 200,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 0,
        "damage" : 130,
        "damage_type" : "割伤",
]),
([      "action" : CYN"$N突然横卧于地，$n目瞪口呆之际，一招「"GRN"破膛刀"CYN"」，手中$w"CYN"由下而上直劈$n的小腹。  "NOR,
        "skill_name" : "破膛刀",
        "force" : 240,
        "dodge" : 5,
        "parry" : 15,
        "lvl" : 8,
        "damage" : 150,
        "damage_type" : "割伤",
]),
([      "action" : CYN"$N足尖一点，一个倒翻头顶着地，一招「"YEL"去魂电"CYN"」，$w"CYN"一闪，自左而右，由右到左连出十刀。  "NOR,
        "skill_name" : "去魂电",
        "force" : 280,
        "dodge" : 10,
        "parry" : 15,
        "lvl" : 16,
        "damage" : 165,
        "damage_type" : "割伤",
]),
([      "action" : CYN"$N怪叫一声，飞腾空中，一招「"BLU"流星经天"CYN"」，手中$w"CYN"脱手而出，疾射$n的$l  "NOR,
        "skill_name" : "流星经天",
        "force" : 320,
        "dodge" : 0,
        "parry" : 5,
        "lvl" : 23,
        "damage" : 170,
        "damage_type" : "割伤",
]),
([      "action" : CYN"$N脸色诡异，喉中“"BLU"呵呵"CYN"”低吼，一招「"YEL"蛇行"CYN"」，$w"CYN"灵动异常的在$n的$l游走过去  "NOR,
        "skill_name" : "蛇行",
        "force" : 350,
        "dodge" : 35,
        "parry" : 25,
        "lvl" : 30,
        "damage" : 180,
        "damage_type" : "割伤",
]),
([      "action" : CYN"$N一招「"HIW"三界咒"CYN"」，手中$w"CYN"微微一抖，“"HIW"嗤嗤嗤"CYN"”三声轻响，向$n头、胸、腹连劈三刀。  "NOR,
        "skill_name" : "三界咒",
        "force" : 320,
        "dodge" : 10,
        "parry" : 25,
        "lvl" : 40,
        "damage" : 210,
        "damage_type" : "割伤",
]),
([      "action" : CYN"$N炸雷般大喝一声，一式「"HIR"魔分身"CYN"」$w"CYN"照$n搂肩带背斜劈下来，力道凶猛，势不可挡。  "NOR,
        "skill_name" : "魔分身",
        "force" : 500,
        "dodge" : 15,
        "parry" : 10,
        "lvl" : 60,
        "damage" : 230,
        "damage_type" : "割伤",
]),
([      "action": CYN"$N高高跃起，挥舞着手中的$w"CYN"一招「"BLU"一柱擎天"CYN"」犹如一条黑蟒般向$n当头直落而下"NOR,
        "dodge": 10,
        "force": 310,
        "damage" : 250,
        "lvl" : 0,
        "damage_type": "割伤"
]),

([  "action": CYN"$N一声暴喝「"YEL"横扫千军"CYN"」！将$w"CYN"由下往上一撩，双手握住$w，转身猛得横扫打向$n的$l"NOR,
        "dodge": 15,
        "force": 350,
        "lvl" : 0,
        "damage": 260,
        "damage_type": "割伤"
]),
([      "action": CYN"$N忽然招数一变，使出「"HIC"灵蛇出洞"CYN"」，刀法显得灵巧之极，手中$w"CYN"化作条条黑影缠向$n"NOR,
        "dodge": 50,
        "force": 400,
        "lvl" : 29,
        "damage": 330,
        "damage_type": "割伤"
]),
([  "action": CYN"$N以刀代剑，$w"CYN"中宫直进，夹着一阵狂风刺出，逼向$n的$l，正是招「"HIB"蛟蛇化龙"CYN"」"NOR,
        "dodge": 15,
        "force": 400,
        "lvl" : 59,
        "damage": 370,
        "damage_type": "刺伤"
]),
([  "action": CYN"$N一式「"HIW"一刀定海"CYN"」，当头一$w"CYN"击将下来，刀头未至，一股风已将$n逼得难以喘气"NOR,
        "dodge": 50,
        "force": 440,
        "lvl" : 79,
        "damage": 380,
        "damage_type": "割伤"
]),
([  "action": CYN"$N变招「"HIR"群魔狂舞"CYN"」，$w"CYN"扫出一道道灰影从四面八方围向$n，要将$n淹没吞食"NOR,
        "dodge": 100,
        "force": 540,
        "lvl" : 89,
        "damage": 390,
        "damage_type": "割伤"
]),
});

string *parry_msg = ({
"$n反手一刺，$w象一条盘蛇，直扑$N的手腕.",
"$n向左侧进一步，手中的$w顺势滑下，急削$N握的手指。\n",
"$n刀法一变，将手中的$w向上一撩,将$N的攻势引偏出去.",
});
int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query_skill("xiangfu-lun") > 100)
		return notify_fail("你有雪山开山祖师的功力?\n");
	if ((int)me->query_skill("longxiang-boruo", 1) < 150)
		return notify_fail("需要有第五层以上龙象般若功火候,才能修炼血海魔刀。\n");
          return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me)
{
        object target, weapon; 
        int i, level, lvl;     
        
        target = offensive_target(me);    
        if (target->query_temp("weapon"))
             weapon = target->query_temp("weapon");
    
        lvl = random((int)me->query_skill("xuehai-modao",1));
      
        if (me->query_skill("xuehai-modao",1) > 100 &&
            me->query("neili") > 1000 && random(5) > 3 &&
            random(me->query("combat_exp")) > (int)target->query("combat_exp")/2){
            me->add("neili", -20);            
//            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
            return ([
                "action": HIC"不等招式用老，$N把手中$w顺势一晃，刀尖直划而下，夹起一股阴风劈向$n！"NOR,
                "force" : 600,
                "dodge" : 200,
                "damage": 510,
                "damage_type":  "割伤"]);  
           } 
            

        level   = (int) me->query_skill("xuehai-modao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query_skill("xiangfu-lun") > 100)
		return notify_fail("你有雪山开山祖师的功力?\n");
	
	if ((int)me->query("jingli") < 60)
		return notify_fail("你的精力不够练血海魔刀。\n");
	me->receive_damage("jingli", 50);
	return 1;
}

int double_attack(object me)
{	
   	if ( me->query_skill("xuehai-modao", 1) >= 80
     	&& me->query_skill_mapped("blade") == "xuehai-modao"
     	&& me->query("zhou/hubo"))
             	return 1;
}
string perform_action_file(string action)
{
        return __DIR__"xuehai-modao/" + action;
}
