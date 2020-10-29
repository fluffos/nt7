// bluesea-force.c 南海玄功

#include <ansi.h>
inherit FORCE;

int is_pbsk() { return 1; }

string *dodge_msg = ({
        "$n暗运内力，$N的进攻就如击到气墙上，没有半点效果。\n",
        "$n大喝一声，一股气流直冲而出，硬生生震退了$N。\n",
        "$n身子一转，一股旋风将$N的招数全部化解。\n",
        "$n哼然冷笑，微微移动，内力回旋使$N的进攻差之毫厘。\n",
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("bluesea-force", 1);
        return lvl * lvl * 20 * 15 / 100 / 200;
}

mapping *actionf = ({
([      "action":"$N跨出一步，一指缓缓戳向$n的$l，笼罩了方圆数寸的范围",
        "force" : 500,
        "attack": 150,
        "dodge" : 90,
        "parry" : 88,
        "damage": 170,
        "damage_type":  "刺伤"
]),
([      "action":"$N一声震喝，随即一掌劈出，中途却忽然一指刺向$n的$l",
        "force" : 510,
        "attack": 165,
        "dodge" : 110,
        "parry" : 90,
        "damage": 160,
        "damage_type":  "刺伤"
]),
([      "action":"$N疾走数步，左掌掌劈向$n的肩头，右手食却点向$n的$l，",
        "force" : 515,
        "attack": 155,
        "dodge" : 85,
        "parry" : 85,
        "damage": 175,
        "damage_type":  "刺伤"
]),
([      "action":"$N深吸一口气，步步进逼，双掌连环劈向$n的$l",
        "force" : 520,
        "attack": 140,
        "dodge" : 80,
        "parry" : 90,
        "damage": 180,
        "damage_type":  "瘀伤"
]),
([      "action":"$N身体原地不动，双掌平推，一股掌力凌空奔$n而去",
        "force" : 535,
        "attack": 135,
        "dodge" : 80,
        "parry" : 95,
        "damage": 170,
        "damage_type":  "内伤"
]),
([      "action":"$N足下暗和八卦，步法变幻莫测，左右掌连翻出击，攻向$n",
        "force" : 500,
        "attack": 150,
        "dodge" : 85,
        "parry" : 115,
        "damage": 165,
        "damage_type":  "震伤"
]),
});

mapping *actionw = ({
([      "action":"$N跨出一步，手中$w缓缓砸向$n，笼罩了方圆数寸的范围",
        "force" : 450,
        "attack": 170,
        "dodge" : 100,
        "parry" : 110,
        "damage": 200,
        "damage_type":  "震伤"
]),
([      "action":"$N一声震喝，手中的$w随即横扫$n，中途却忽然刺向$n的$l",
        "force" : 460,
        "attack": 165,
        "dodge" : 80,
        "parry" : 110,
        "damage": 220,
        "damage_type":  "刺伤"
]),
([      "action":"$N疾走数步，左掌掌劈向$n的肩头，右手的$w却点向$n的$l，",
        "force" : 480,
        "attack": 175,
        "dodge" : 85,
        "parry" : 100,
        "damage": 210,
        "damage_type":  "刺伤"
]),
([      "action":"$N深吸一口气，步步进逼，手中的$w连环劈向$n的$l",
        "force" : 475,
        "attack": 180,
        "dodge" : 75,
        "parry" : 120,
        "damage": 205,
        "damage_type":  "瘀伤"
]),
([      "action":"$N身体原地不动，手中的$w一划，一股内力凌空奔$n而去",
        "force" : 480,
        "attack": 175,
        "dodge" : 80,
        "parry" : 125,
        "damage": 210,
        "damage_type":  "割伤"
]),
([      "action":"$N足下暗合八卦，步法变幻莫测，手中的$w化作数道光芒，攻向$n",
        "force" : 490,
        "dodge" : 160,
        "parry" : 110,
        "damage": 220,
        "damage_type":  "内伤"
]),
});

string *usage_skills = ({ "finger", "strike", "staff", "dodge",
                          "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_force(string force) { return 1; }

int valid_combo(string combo)
{
        return combo == "bluesea-force" ||
               combo == "tanzhi-shentong";
}

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -80;
        int d_e2 = -100;
        int p_e1 = -80;
        int p_e2 = -100;
        int f_e1 = 450;
        int f_e2 = 630;
        int m_e1 = 440;
        int m_e2 = 540;
        int i, lvl, seq, ttl;
        mapping *action;

        if (objectp(weapon))
                action = actionw;
        else
                action = actionf;

        ttl = sizeof(action);
        lvl = (int) me->query_skill("bluesea-force", 1);
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
                "damage_type" : action[seq]["damage_type"],
        ]);
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;

        if( query("combat_exp", me)<3000000 )
                return notify_fail("你觉得南海玄功深奥之极，"
                                   "凭自己的战斗经验一时间难以领会。\n");

        if ((int)me->query_skill("martial-cognize", 1) < 50)
                return notify_fail("你觉得南海玄功过于深奥之极，以"
                                   "自己的武学修养全然无法明白。\n");

      if( query("character", me) != "心狠手辣" && 
          query("character", me) != "国士无双" )
                return notify_fail("你发觉南海神功招招狠、式式险，舍"
                                   "生忘死，自己实在领会不了。\n");

        if( query("con", me)<22 && me->query_con()<63 )
                return notify_fail("你试图运用真力修炼南海玄功，却突"
                                   "然觉得眼前一黑，看来是根骨不好，"
                                   "不能勉强修行。\n");

        if( query("gender", me) == "无性" && 
            (int)me->query_skill("bluesea-force", 1) > 219)
                return notify_fail("你无根无性，阴阳不调，难以领会高深的南海玄功。\n");

        level = me->query_skill("bluesea-force", 1);

        if ((int)me->query_skill("martial-cognize", 1) < level)
                return notify_fail("你觉得自己的武学修养有限，难以领会更高深的南海玄功。\n");

        for (i = 0; i < sizeof(usage_skills); i++)
                if (me->query_skill(usage_skills[i], 1) < level)
                        return notify_fail("你对" + to_chinese(usage_skills[i]) +
                                           "的理解还不够，无法继续领会更高深的南海玄功。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("南海玄功博大精深，无法简单的通过练习进步。\n");
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("bluesea-force", 1) < 200
         || !living(me) || query("neili", me)<500
        ||  me->query_skill_mapped("parry") != "bluesea-force")
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("bluesea-force", 1);

        if (ap / 2 + random(ap) < dp)
        {
                addn("neili", -300, me);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIB "$n" HIB "默运南海玄功，真气护住全身。$N" HIB
                                            "一招击中$n" HIB "，只觉落手处劲力石沉大海，"
                                            "大感惊讶，连忙退回。 \n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIB "$N" HIB "一招攻出，$n" HIB "怒吼一声，不退"
                                            "反进，巨涛般的气墙竟将$N" HIB "这招逼回。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIB "$n" HIB "全身真气流动，一股罡气护住全身，已将$N" HIB "所"
                                            "有进攻招式挡在罡气之外。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "默运南海玄功，护住全身。但是$N" HIY
                                 "内力深厚无比，冷笑一声，一招竟结实地打在$n" HIY
                                 "身上。\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "不退反进，试图将$N" HIY "的招式逼回。但是"
                                 "$N" HIY "招式陡然一变，$n" HIY "顿时一惊，却已然中招。\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "一股护体罡气欲将$N" HIY "的进攻"
                                 "招式封死。但是$N" HIY "早已看去其中玄虚，冷笑一声，$N" HIY
                                 "却已中招。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
         }
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if (me->is_busy()
           || random(2) == 0
           || ! living(victim)
           || damage_bonus < 120
            || query("neili", me)<200
           || me->query_skill("bluesea-force", 1) < 250)
                return 0;


        if (damage_bonus / 2 > victim->query_con())
        {
                addn("neili", -100, me);
                victim->receive_wound("qi", (damage_bonus - 88) / 2, me);
                addn("neili", -((damage_bonus-random(80))/2), victim);

                return random(2) ? HIR "$N" HIR "灌注全身劲力如南海巨涛般袭向$n" HIR "周身大穴，$n" HIR "根本无法抵挡，立受内伤，鲜血狂吐！" NOR:
                                   HIR "$n" HIR "硬接$N" HIR "一招，不想对方内力如海浪般袭来，$n" HIR "猛的吐出一口鲜血，看来已受内伤！\n" NOR;
        }
}

int difficult_level()
{
        return 500;
}

string perform_action_file(string action)
{
        return __DIR__"bluesea-force/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"bluesea-force/exert/" + action;
}
