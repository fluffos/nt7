// yinyang-shiertian.c 阴阳十二重天
// 三十岁之前通晓九阳神功、九阴神功、北冥神功、凌波微步、乾
// 坤大挪移、降龙十八掌和六脉神剑，合其为一创出，S+++级武学。
// 阴阳十二重天可以激发为天下所有的武功。

#include <ansi.h>

inherit FORCE;

int is_ultimate_skill() { return 1; }

string *xue_name = ({ 
"劳宫穴", "膻中穴", "曲池穴", "关元穴", "曲骨穴", "中极穴", "承浆穴", "天突穴", "百会穴",
"幽门穴", "章门穴", "大横穴", "紫宫穴", "冷渊穴", "天井穴", "极泉穴", "清灵穴", "至阳穴", });

string *attack_name = ({
"九阳六脉剑气", "九阴六脉剑气", "九阳无极劲", "九阴无极劲", "九阴太玄劲","九阳太玄劲" });

string *dodge_msg = ({
        HIW "$n" HIW "手足忽的一晃，$N" HIW "竟然无法进击，只能自保。\n" NOR,
        HIW "只见$n" HIW "身子轻轻晃动，$N" HIW "眼前顿时出现了无数个$n" HIW
        "的幻影，令$N" HIW "完全无法辨出虚实。\n" NOR,
        HIW "$n" HIW "往旁边歪歪斜斜的迈出一步，却恰好令$N" HIW "的攻击失之"
        "毫厘。\n" NOR,
        HIW "$N" HIW "这一招来的好快，然后$n" HIW "一闪，似乎不费半点力气，"
        "却将$N" HIW "这一招刚好避开。\n" NOR,
        HIW "但见$n" HIW "轻轻一跃，已不见了踪影，$N" HIW "心中大骇，却又见"
        "$n" HIW "擦肩奔过，步法之奇巧，当真令人思索菲仪。\n" NOR,
});

string *parry_msg = ({
        HIW "$N" HIW "一招击在$n" HIW "身上，却被$n" HIW "暗运乾坤大挪移内劲"
        "，将内力尽数移入地下。\n" NOR,
        HIW "$n轻轻一带，$N" HIW "发现自己招数回击过来，吓得往后倒退几步。\n" NOR,
        HIW "$n手臂回转，在$N" HIW "手肘下轻轻一推，$N" HIW "招数落空。\n" NOR,
        HIW "$n右手伸出，在$N" HIW "手腕上轻轻一拉，$N" HIW "收势不住，直往前扑去。\n" NOR,
        HIW "$n身形不动，$N" HIW "一招击下，有如石沉大海，不觉呆住了。\n" NOR,
        HIW "$n左牵右引，$N" HIW "如身处漩流，连续转了好几个圈。\n" NOR,
        HIW "$n双手回圈，$N" HIW "只觉得前面好象有一堵墙，再也攻不进去。\n" NOR,
        HIW "$n轻轻一转，$N" HIW "一招击在地上，只打得尘土飞扬。\n" NOR,
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("yinyang-shiertian", 1);
        return lvl /10 * lvl /10 * 15 * 40 / 10 / 20;
}

int query_jingli_improve(object me)
{
        int lvl;
        
        lvl = (int)me->query_skill("yinyang-shiertian", 1);
        
        if (me->query_skill_mapped("force") == "yinyang-shiertian")
                return lvl * 14 / 7;

        return 0;
}

mapping *actionf = ({
([      "action": HIW "$N" HIW "右手中指一竖，「六脉神剑」向前刺出。真气鼓荡，嗤"
                  "然声响，无形剑气直指$n" HIW,
        "force" : 700,
        "attack": 300,
        "dodge" : 450,
        "parry" : 450,
        "damage": 550,
        "weapon": HIW "破体无形剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "action": HIR "$N" HIR "身体一侧，一掌凌空劈出，一股炽热无比的气流顿时澎"
                  "湃涌至$n" HIR "全身各处",
        "force" : 800,
        "attack": 400,
        "dodge" : 350,
        "parry" : 350,
        "damage": 250,
        "weapon": HIR "九阳无极劲" NOR,
        "damage_type":  "割伤"
]),
([      "action": HIY "$N" HIY "身形一转，拳头携着疾速旋转的气流挥出，疾如闪电，"
                  "势如雷霆，击向$n" HIY,
        "force" : 800,
        "attack": 400,
        "dodge" : 350,
        "parry" : 350,
        "damage": 250,
        "weapon": HIY "九阴无极劲" NOR,
        "damage_type":  "刺伤"
]),
([      "action": WHT "$N" WHT "双掌平平提到胸前，神色沉重的缓缓施出「降龙十八掌"
                  "」推向$n" WHT "全身各处",
        "force" : 1000,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 200,
        "weapon": WHT "降龙无极劲" NOR,
        "damage_type": "刺伤"
]),
([      "action": HIW "$N" HIW "双手十指齐伸，数十条气流从少冲穴中激射而出，「六"
                  "脉神剑」出手如风，指向$n" HIW,
        "force" : 700,
        "attack": 300,
        "dodge" : 450,
        "parry" : 450,
        "damage": 550,
        "weapon": HIW "破体无形剑气" NOR,
        "damage_type":  "刺伤"
]),
([      "action": WHT "$N" WHT "突然身形飞起，双掌居高临下一招「降龙十八掌」在呼"
                  "啸声中迅捷无比地劈向$n" WHT "全身各处",
        "force" : 1000,
        "attack": 450,
        "dodge" : 200,
        "parry" : 200,
        "damage": 200,
        "weapon": WHT "降龙无极劲" NOR,
        "damage_type": "刺伤"
]),
});

mapping *actionw = ({
([      "action": HIY "$N" HIY "攻势忽缓而不疏，$w" HIY "变化无常，捉摸不定向$n"
                  HIY "慢慢卷去",
        "force" : 600,
        "attack": 300,
        "dodge" : 300,
        "parry" : 300,
        "damage": 400,
        "damage_type": "内伤"
]),
([      "action": HIY "$N" HIY "手中的$w" HIY "突焕气象森严，便似千军万马奔驰而"
                  "来，如同棍棒一般横扫$n" HIY,
        "force" : 600,
        "attack": 300,
        "dodge" : 300,
        "parry" : 300,
        "damage": 400,
        "damage_type": "内伤"
]),
([      "action": HIY "$N" HIY "卷起手中的$w" HIY "，就如铁锤一般对着$n" HIY "乱"
                  "砍乱砸，没有半点章法",
        "force" : 600,
        "attack": 300,
        "dodge" : 300,
        "parry" : 300,
        "damage": 400,
        "damage_type": "内伤"
]),
([      "action": HIY "$N" HIY "运用$w" HIY "幻化做一个一个圆圈，似乎要将$n" HIY
                  "团团包围",
        "force" : 600,
        "attack": 300,
        "dodge" : 300,
        "parry" : 300,
        "damage": 400,
        "damage_type": "内伤"
]),
([      "action": HIY "$N" HIY "含笑回转$w" HIY "，伸手一指，颇得拈花指之意，点"
                  "向$n" HIY "全身",
        "force" : 600,
        "attack": 300,
        "dodge" : 300,
        "parry" : 300,
        "damage": 400,
        "damage_type": "内伤"
]),
});

string main_skill()
{
        return "yinyang-shiertian";
}

mapping sub_skills = ([
        "moon-blade"  : 350,
        "jiuyang-shengong" : 350,
        "taixuan-gong"     : 350,
        "six-finger"       : 350,
        "dragon-strike"    : 350,
        "qiankun-danuoyi"  : 350,
        "wuming-jianfa"    : 350,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
//      object ob;

        if( query("int", me)<39 )
        {
                tell_object(me, "你演练完毕，只感思绪紊乱，看来依你的悟性，无"
                                "法将其合一。\n");
                return 0;
        }
        if( query("con", me)<39 )
        {
                tell_object(me, "你演练完毕，只觉全身真气乱窜，眼冒金星，两耳轰鸣，好"
                                "不容易才控制下来。\n");
                return 0;
        }
        if( query("str", me)<39 )
        {
                tell_object(me, "你演练完毕，只觉双臂酸疼，全身发软。\n");
                return 0;
        }
        if( query("dex", me)<39 )
        {
                tell_object(me, "你演练完毕，发现依你的身法暂时还无法将其融会贯通。\n");
                return 0;
        }

        if( query("age", me) >= 18 )
        {
                                tell_object(me, "你已错过演练的最佳时刻，今生将于此高深武学无缘。\n");
                return 0;
        }

        if (random(100) != 1 && ! wizardp(me))
        {
                tell_object(me, "你觉得有所感悟，或许再演练一次就能融会贯通，练成阴阳九转十二重天。\n");
                return 0;
        }

        tell_object(me, HIW "一阵凡尘往事涌上心头，你几欲放声长叹。霎那间，你放眼回首，竟有一股莫名\n"
                        "的悲哀。宗师泰斗那种高出不胜寒、登泰山而小天下之感犹然而生，你只觉得以\n往的"
                        "武学现在看来是多么的渺小可笑。\n" NOR);

        CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name() + "演练出"HIY"阴阳九转十二重天"HIM"。\n");
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

string *usage_skills = ({ "unarmed", "strike", "claw", "hand", "cuff", "finger",
                          "sword", "blade", "hammer", "throwing", "club", "whip",
                          "staff", "dodge", "dagger", "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_force(string force)
{
        return 1;
}

int double_attack()
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;

        level = me->query_skill("yinyang-shiertian", 1);
        for (i = 0; i < sizeof(usage_skills); i++)
                if (me->query_skill(usage_skills[i], 1) < level)
                        return notify_fail("你对" + to_chinese(usage_skills[i]) + "的理解还"
                                           "不够，无法继续领会更高深的阴阳十二重天。\n");

        if (me->query_skill("martial-cognize", 1) < level)
                                return notify_fail("你武学修养不够，无法继续修炼。\n");
        
        if( level>380 && query("yinyang-shiertian/yinyang", me) )
                                return notify_fail("你阴阳九转十二重天已达到新的层次，须修炼出阴阳境界方能再次提升。\n");
        
        if( level>480 && query("yinyang-shiertian/qiankun", me) )
                                return notify_fail("你阴阳九转十二重天已达到新的层次，须修炼出乾坤境界方能再次提升。\n");

        if( level>600 && query("yinyang-shiertian/shier", me) )
                                return notify_fail("你阴阳九转十二重天已达到新的层次，须修炼出十二重天境界方能再次提升。\n");      

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("阴阳十二重天博大精深，无法简单的通过练习进步。\n");
}

int difficult_level()
{
        return 3000;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name1, name2/*, weapon*/;
        name1 = xue_name[random(sizeof(xue_name))];
        name2 = attack_name[random(sizeof(attack_name))];

        victim->receive_wound("qi", damage_bonus * 3, me);
        addn("neili",query("jiali",  me)/3, me);

        if( query("neili", victim)<500 )
                set("neili", 0, victim);
        else
                addn("neili", -300, victim);

        return NOR + HIR "$n" HIR "接下$N" HIR "一招，" + name2 + "顿时破体而"
               "入，全身真气由" + name1 + "狂泻而出。\n" NOR;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;

        ap = ob->query_skill("parry");
        dp = me->query_skill("yinyang-shiertian", 1);

        if (random(ap * 2 / 3) < dp * 3 / 2)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIW "$n" HIW "面含微笑，轻轻一格，已将天"
                                            "下所有进攻招数全部封死。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$n" HIW "眉头微微一皱，动也不动，将"
                                            "$N" HIW "震到一边。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$n" HIW "身形微微一抖，已将$N" HIW 
                                            "迫退至丈许开外。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "$n" HIW "一声轻哼，身形微微一动，已"
                                            "飘然远去，使$N" HIW "的进攻全无用处。\n" NOR]);
                        break;
                }
                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("yinyang-shiertian", 1);
        if (lvl < 200) return 100;
        if (lvl < 250) return 150;
        if (lvl < 350) return 180;
        return 200;
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("yinyang-shiertian", 1);
        if (lvl < 200) return 100;
        if (lvl < 250) return 150;
        if (lvl < 350) return 180;
        return 200;
}

string perform_action_file(string action)
{
        return __DIR__"yinyang-shiertian/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"yinyang-shiertian/exert/" + action;
}

void skill_improved(object me) 
{ 
        int i; 
        string *sub_skillnames; 

        sub_skillnames = keys(sub_skills); 
        for (i = 0; i < sizeof(sub_skillnames); i++) 
                me->delete_skill(sub_skillnames); 
} 