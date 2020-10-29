//jiuyin-baiguzhao.c 九阴白骨爪

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

int is_pbsk() { return 1; }

mapping *action = ({
([      "action": "$N左爪虚晃，右爪蓄力，一招「勾魂夺魄」直插向$n的$l",
        "force" : 250,
        "attack": 45,
        "dodge" : 10,
        "parry" : 18,
        "damage": 30,
        "lvl"   : 0,
        "skill_name" : "勾魂夺魄" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N双手连环成爪，爪爪钩向$n，「九子连环」已向$n的$l抓出",
        "force" : 270,
        "attack": 50,
        "dodge" : 20,
        "parry" : 26,
        "damage": 45,
        "lvl"   : 40,
        "skill_name" : "九子连环" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N双手使出「十指穿心」，招招不离$n的$l",
        "force" : 300,
        "attack": 60,
        "dodge" : 20,
        "parry" : 32,
        "damage": 45,
        "lvl"   : 70,
        "skill_name"  : "九子连环" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N身形围$n一转，使出「天罗地网」，$n的$l已完全笼罩在爪影下",
        "force" : 340,
        "attack": 85,
        "dodge" : 30,
        "parry" : 55,
        "damage": 55,
        "lvl"   : 100,
        "skill_name" : "天罗地网" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N使一招「风卷残云」，双爪幻出满天爪影抓向$n全身",
        "force" : 370,
        "attack": 110,
        "dodge" : 40,
        "parry" : 68,
        "damage": 70,
        "lvl"   : 130,
        "skill_name" : "风卷残云" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N吐气扬声，一招「唯我独尊」双爪奋力向$n天灵戳下",
        "force" : 420,
        "attack": 140,
        "dodge" : 50,
        "parry" : 85,
        "damage": 90,
        "lvl"   : 160,
        "skill_name" : "唯我独尊" ,
        "damage_type" : "抓伤"
]),
});

int valid_enable(string usage) { return usage=="claw" || usage=="parry"; }
int valid_combine(string combo) { return combo=="cuixin-zhang"; }
int valid_learn(object me)
{
        if( query("character", me) != "心狠手辣" && query("character", me) != "国士无双" )
                return notify_fail("你天性不符，受其拘束，无法领会九阴白骨爪的妙旨。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练九阴白骨爪必须空手。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的内力太弱，无法练九阴白骨爪。\n");

        if ((int)me->query_str() < 30)
                return notify_fail("你现在膂力孱弱，还无法练九阴白骨爪。\n");

        if ((int)me->query_skill("force") < 90)
                return notify_fail("你的内功太差，无法练九阴白骨爪。\n");

        if ((int)me->query_skill("claw", 1) < 60)
                return notify_fail("你的基本爪法太差，无法领会九阴白骨爪。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("jiuyin-baiguzhao", 1))
                return notify_fail("你的基本爪法火候不够，无法领会更高深的九阴白骨爪。\n");

        return 1;
}
int practice_skill(object me)
{
//      object obj;
        object *obs;
        int /*i,*/ skill/*, damage*/;

        skill = me->query_skill("jiuyin-baiguzhao", 1);
        if( query("qi", me)<100 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够练九阴白骨爪。\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("这里不能练功。\n");

        if( query("sleep_room", environment(me)) )
                return notify_fail("这里练功会打扰别人休息。\n");

        if (skill < 200)
        {
                obs = filter_array(all_inventory(environment(me)),
                                   (: (base_name($1) == CORPSE_OB &&
                                       !query("been_cut/head", $1) ||
                                       base_name($1) == "/clone/misc/head") &&
                                       query_temp("clawed_by_jiuyin", $1)<10:));
                if (sizeof(obs) < 1)
                        return notify_fail("练九阴白骨抓需有尸体或是完好的头盖骨。\n");

                addn("neili", -450, me);
        }

        me->receive_damage("qi", 80);
        addn("neili", -40, me);
        if (skill < 200)
        {
                message_vision(HIB "只见$N" HIB "左手上圈下钩、左旋右转，连变了"
                               "七八般花样，蓦地里右手一伸，噗的一响，五根手指直"
                               "插入\n头骨的脑门。随后五根手指" HIR "血淋淋"
                               HIB "的提将起来。\n" NOR, me);

                if (base_name(obs[0]) == "/clone/misc/head")
                        obs[0]->set("long",query("long", obs[0])+
                                    "上面赫然有五个小洞，伸手一探，刚好可以插入。\n");

                addn_temp("clawed_by_jiuyin", 1, obs[0]);
                me->improve_skill("jiuyin-baiguzhao", 100 + skill * 5 + random(500));
        }

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
        int d_e1 = 20;
        int d_e2 = 5;
        int p_e1 = -20;
        int p_e2 = -60;
        int f_e1 = 300;
        int f_e2 = 600;
        int /*i,lvl,*/ seq, ttl = sizeof(action);

        seq = random(ttl);       /* 选择出手招数序号 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "抓伤" : "内伤",
        ]);
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me)
{
        if( query("shen", me) <= -100000)return 1;
        else if( query("shen", me)<0)return 0.8;
        else return 0.6;
}

void skill_improved(object me)
{
        tell_object(me, HIR"你忽然从心底生出一股恶念：杀、杀、杀！我要杀绝天下人！\n" NOR );
        addn("shen", -200, me);
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;
        mixed result;

        lvl  = me->query_skill("jiuyin-baiguzhao", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (damage_bonus / 2 > victim->query_str())
        {
            victim->affect_by("jy_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id":query("id", me),
                                 "duration" : lvl / 100 + random(lvl / 10) ]));
                result = ([ "damage" : damage_bonus ]);
                result += ([ "msg" : HIR "你听到「喀啦」一声轻响，竟似是骨碎的声音！\n" NOR ]);

                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("jiuyin-baiguzhao", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
string perform_action_file(string action)
{
        return __DIR__"jiuyin-baiguzhao/" + action;
}

int help(object me)
{
        write(HIC"\n九阴白骨爪："NOR"\n");
        write(@HELP

    徽宗皇帝于政和年间，遍搜普天下道家之书，雕版印行，一共
有五千四百八十一卷，称为‘万寿道藏’。皇帝委派刻书之人，叫
做黄裳。他生怕这部大道藏刻错了字，皇帝发觉之后不免要杀他的
头，因此上一卷一卷的细心校读。他居然便因此精通道学，更因此
而悟得了武功中的高深道理。他无师自通，修习内功外功，竟成为
一位武功大高手。他因此涉及江湖仇杀，退隐山林。不知不觉竟已
过了四十多年，终于对每一个敌人所使过的招数，他都想通了破解
的法子对付。于是出得山来，去报仇雪恨。不料那些敌人全都已不
在人世了。黄裳心想：‘原来我也老了，可也没几年好活啦。’他
花了这几十年心血，想出了包含普天下各家各派功夫的武学，过得
几年，这番心血岂不是就此湮没？于是他将所想到的法门写成了上
下两卷书，那就是《九阴真经》。九阴白骨爪就是依此书练成的霸
道功夫。

        学习要求：
                内力200
HELP
        );
        return 1;
}