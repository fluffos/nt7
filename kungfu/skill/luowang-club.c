// This program is a part of NITAN MudLIB
// luowang-club.c 紧那罗王棍

#include <ansi.h> 
#include <combat.h>

inherit SKILL; 

mapping *action = ({ 
([      "action" :
       "$N手中的棍梢由下往上一撩,紧接着一招[顺风打旗],那棍尾直 往$n的$l打去",     
       "force"  : 350, 
       "attack" : 220, 
       "dodge"  : -10, 
       "parry"  : -100, 
       "damage" : 230, 
       "damage_type": "淤伤" 
]), 
([      "action" :"$N单腿点地，向上拔出丈余，$w飞舞幻出无数幻影将
$n罩住，口中大喝一声[雪花盖顶]，只听棍带风声呜呜作响向$n的$1劈去",     
       "force"  : 380, 
       "attack" : 200, 
       "dodge"  : -5, 
       "parry"  : -80, 
       "damage" : 250, 
       "damage_type": "淤伤" 
]), 
([      "action" : "$N把$w一架，挡住了$n的去路，$N手中的$w一振，带起了万丈金光，
　　　从这片光芒中冲出一道清烟，直向$n的$1奔去，正是一招［拨云见日］",
       "force"  : 400, 
       "attack" : 200, 
       "dodge"  : -40, 
       "parry"  : -105, 
       "damage" : 280, 
       "damage_type": "刺伤" 
]), 
([      "action" :       "$N手中的$w一振，以棍行刀式，大开大阖,       
       $w化做六道黑影向$n的$1集中劈去",      
       "force"  : 420, 
       "attack" : 180, 
       "dodge"  : -15, 
       "parry"  : -80, 
       "damage" : 280, 
       "damage_type": "淤伤" 
]), 
([      "action" : "$N身体向后一转,大喝:[乌龙摆尾],$w化做数道幻影扫向$n的腰部", 
       "force"  : 420, 
       "attack" : 190, 
       "dodge"  : -10, 
       "parry"  : -100, 
       "damage" : 290, 
       "damage_type": "震伤"
]), 
([     "action" : "$N身行一展,化为[燕子穿林]式,手中的$w快如闪电地刺向$n的的$l",
       "force"  : 450,
       "attack" : 150,
       "dodge"  : -20,
       "parry"  : -120,
       "damage" : 310,
       "damage_type": "刺伤"
]), 
([     "action" : "$N身体往后一顿,换以握枪的手法,一式[蛟龙出水],手中的$w往$n的$l刺去",
       "force"  : 520, 
       "force" : 460, 
       "attack" : 160, 
       "dodge"  : -40, 
       "parry"  : -100, 
       "damage" : 90, 
       "damage_type": "刺伤" 
]), 
([      "action" : "$N手中的$w舞了个棍花，单腿独立，$w向后一带，口中大喝一声
　　　　[独劈华山]，只听$w带一声呼啸向$n的$1劈去",
       "force"  : 490, 
       "attack" : 220, 
       "dodge"  : -10, 
       "parry"  : -75, 
       "damage" : 320, 
       "damage_type": "淤伤" 
]), 
([      "action" : "$N腰一摆，双腿顺势盘腿坐下，手中$w一抖，一式［犀牛望月],
       手中的$w势如长虹，由下往$n的$1刺去",    
       "force"  : 500, 
       "attack" : 150, 
       "dodge"  : -30, 
       "parry"  : -110, 
       "damage" : 340, 
       "damage_type": "刺伤" 
]), 
([      "action" : "$N手中的$w左右拦扫，一把把$n圈住,紧接着，$N用$w把$n一挑?      
        长啸一声:[罗汉搏虎],棍梢径直向$n的$1劈去",           
       "dodge"  : -25, 
       "force"  : 500, 
       "attack" : 170, 
       "dodge"  : -70, 
       "parry"  : -55, 
       "damage" : 350, 
       "damage_type": "淤伤" 
]), 
([      "action" : "$N使出一招[天马行空],手中的$w轻盈自如地挥洒，向$n的$1点击过去",
       "force" : 510, 
       "attack" : 185, 
       "dodge"  : -30, 
       "parry"  : -100, 
       "damage" : 410, 
       "damage_type": "淤伤" 
]), 
([      "action" :        "$N一声长吟，$w向外一拨身体顺势急转，突然急停向
        $n的身前跃去，口中长啸「凤凰展翅」棍梢横扫$n的$l",    
       "force"  : 510, 
       "attack" : 180, 
       "dodge"  : -50, 
       "parry"  : -110, 
       "damage" : 410, 
       "damage_type": "淤伤" 
]), 
([       "action" : "$N双目精光暴长，神情怒不可遏，一式[横扫千军]带动
       无数道黑影,$w直击$n的$l不待$n做出反应，$w竟然毫无章法似的向$n全身
       乱劈过去,速度极快$n只觉眼前尽是棍影而不见人",     
       "force"  : 560, 
       "attack" : 170, 
       "dodge"  : -65, 
       "parry"  : -120, 
       "damage" : 500, 
       "damage_type": "淤伤" 
]), 
}); 

string main_skill() { return "luowang-club"; } 

mapping sub_skills = ([ 
       "shunfeng-daqi"         : 120,        // 1 
       "xuehua-gaiding"        : 120,        // 2 
       "boyun-jianri"          : 120,        // 3
       "liuding-kaishan"       : 120,        // 4
       "wulong-baiwei"         : 120,        // 5
       "yanzi-chuanlin"        : 120,        // 6
       "jiaolong-chushui"      : 120,        // 7
       "dupi-huashan"          : 120,        // 8
       "xiniu-wangyue"         : 120,        // 9
       "luohan-bohu"           : 120,        // 10
       "tianma-xingkong"       : 120,        // 11
       "fenghuang-zhanchi"     : 120,        // 12
       "hengsao-qianjun"       : 120,        // 13
]); 

int get_ready(object me) 
{ 
       return 1; 
} 

int get_finish(object me) 
{ 
       if( query("str", me)<25 || me->query_str()<45 )
       { 
               tell_object(me, "你演练完毕，整个身体几乎完全虚脱了，软绵绵的提不起一点劲。\n"); 
               return 0; 
       } 

       if( query("con", me)<25 || me->query_con()<45 )
       { 
               tell_object(me, "你演练完毕，就觉得眼前金星乱冒，太阳穴突突的跳。\n"); 
               return 0; 
       } 

       if ((int)me->query_skill("force") < 200) 
       { 
               tell_object(me, "你演练完毕，几乎虚脱，自己的内功水平看来还有待提高。\n"); 
               return 0; 
       } 

       if( query("max_neili", me)<1500 )
       { 
               tell_object(me, "你演练完毕，丹田提不起半点力来，看来应该继续锻炼内力。\n"); 
               return 0; 
       } 

       if (random(10) < 5) 
       { 
               tell_object(me, "你对紧那罗王棍的奥妙颇有领悟，或许再演练一次就能够融会贯通。\n"); 
               return 0; 
       } 

       tell_object(me, HIY "你一气呵成，将紧那罗王棍从头到尾演练了一变，心中顿悟，通\n" 
                           "晓了的紧那罗王棍奥妙精髓，融会贯通了棍法的精微之处，\n" 
                           "再也不是拆开使用那么那么简单。\n" NOR); 
       return 1; 
} 

mapping query_sub_skills() 
{ 
       return sub_skills; 
} 

int valid_enable(string usage) { return usage=="club" ||  usage=="parry"; }   

int valid_learn(object me) 
{  
        object weapon;
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "club" )
                return notify_fail("你手中无棍怎么学习啊。\n");
       if( query("str", me)<25 && 
           query("con", me)<25 )
               return notify_fail("就你这身子骨还练紧那罗王棍？小心身体吃不消啊。\n"); 
       if( query("int", me)<20 )
               return notify_fail("算了吧，你先天悟性不好，怎么能理解呢。\n"); 
       if ((int)me->query_skill("force") < 200) 
               return notify_fail("你的内功火候不够，无法学习紧那罗王棍。\n"); 
       if ((int)me->query_skill("hunyuan-yiqi") < 200) 
               return notify_fail("你的混元一气功火候不够，无法学习紧那罗王棍。\n");
       if((int)me->query_skill("zui-gun") < 200) 
               return notify_fail("你的醉棍火候不够，无法学习紧那罗王棍。\n"); 
       if ((int)me->query_skill("buddhism") < 200) 
               return notify_fail("你的禅宗心法火候不够，无法学习于禅宗息息相关紧那罗王棍。\n"); 
       if( query("max_neili", me)<2000 )
               return notify_fail("你的内力这么差，怎能融会贯通紧那罗王棍？\n"); 

       if ((int)me->query_skill("club", 1) < 200) 
               return notify_fail("你的基本棍法火候不够，无法学习紧那罗王棍。\n"); 
       if ((int)me->query_skill("club", 1) < (int)me->query_skill("luowang-club", 1)) 
       return
   notify_fail("你的基本棍法水平有限，无法领会更高深的紧那罗王棍。\n"); 

       return 1; 
} 

mapping query_action(object me, object weapon) 
{ 
       mapping a_action;
       int level;

       level = (int)me->query_skill("luowang-club", 1);
       a_action = action[random(sizeof(action))]; 
       a_action["dodge"] -= level / 10;
       a_action["parry"] -= level / 10;
       a_action["attack"] += level / 10;
       a_action["force"] += level / 10;
       a_action["damage"] += level / 10;
       if( query_temp("action_flag", me) )
                set_temp("action_msg", "紧跟着", me);
       return a_action;
} 

int practice_skill(object me) 
{ 
        object weapon;
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "club" )
                return notify_fail("你手中无棍怎么练啊。\n");
     if( query("qi", me)<150 )
               return notify_fail("你的体力太低了。\n"); 
       if( query("neili", me)<100 )
               return notify_fail("你的内力不够练紧那罗王棍。\n"); 

       me->receive_damage("qi", 120); 
       addn("neili", -50, me);
       return 1; 
} 

mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        if (random(10) >= 1)
       { 
               victim->receive_wound("qi", damage_bonus); 
               victim->receive_wound("jing", damage_bonus); 
               return HIR "随着一声沉闷的哼声传来，$n的口中咳出了几口鲜血！\n" NOR; 
       } 
} 

string perform_action_file(string action) 
{ 
       return __DIR__"luowang-club/" + action; 
} 

void skill_improved(object me) 
{ 
       int i; 
       string *sub_skillnames; 

       sub_skillnames = keys(sub_skills); 
       for (i = 0; i < sizeof(sub_skillnames); i++) 
               me->delete_skill(sub_skillnames); 
} 
void do_interlink(object me, object victim)
{
        int skill, i, j;
        object *enemy;
        object weapon;
    
        skill = me->query_skill("luowang-club", 1);
        if( skill>120 && !objectp(weapon=query_temp("weapon", me)) )
        {
                enemy=me->query_enemy();
                if (! sizeof(enemy)) return;
                for (i=0;i<sizeof(enemy);i++)
                {
                        for (j=0;j<(skill/(60*sizeof(enemy)));j++)
                        if( (me->is_fighting(enemy[i]) || enemy[i]->is_fighting(me)) && query("qi", enemy[i])>0 )
                        {
                                if (environment(me) == environment(enemy[i]))
                                {
                                        addn_temp("str", skill/10, me);
                                        addn_temp("dex", skill/10, me);
                                        COMBAT_D->do_attack(me,enemy[i],query_temp("weapon", me),TYPE_REGULAR);
                                }
                        } else break;
                }
                delete_temp("str", me);
                delete_temp("dex", me);
        }
}

