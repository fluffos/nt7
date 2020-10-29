// super-strike 铁掌掌法
// 2006-2-26
inherit SKILL;
#include <ansi.h>

string *parry_msg = ({
"$N双掌一翻，将$n的来势尽数化去，$n急劲就似钻入了一片粘稠之物中间一般。\n",
"$N右肩斜闪，左手手指凭空划了几个圈子，以四两微力，拨动$n千斤巨力。\n",
"$N眼见$n攻到，当即使出一招「天罗地网」，双掌密不透风。\n",
"不料$N双手一圈，一股雄浑无比的力道组成了一个旋涡，只带得$n在原地急转七八下。\n",
"$N连消带打，双手成圆形击出，登时便套得$n跌跌撞撞，身不由主的立足不稳。\n",
"$N使出一招「穿云手」，左手高，右手低，一股罡气已将$n震开。\n",
"$N吸一口气，体内真气流转，右掌挥出，一拒一迎，将$n的力道尽行碰了回去。\n",
"$N双掌一翻，使出一招「穿云手」，双掌柔到了极处，空明若虚，将$n的急劲尽数化去。\n",
"就在这电光石火的一瞬之间，$N身子一弓，$n的劲力登时落空。\n",
});

string  *msgc = ({
"$N下半身右脚撇步上前，双手化掌，向前双抄上击$n的$l",
"$N身体向前冲出，双手先抱回腰际後，再向前以双撑掌直推而出",
"$N全身原步右转，右手向右刁出，左手顺势护肩，抓向$n的$l",
"$N一式[拍案齐掌」，全身微向下坐，产生後拉之势，收左手，右手化掌向前直压而出",
"$N向前一招「双龙探爪」，双手变掌为爪，先右後左，连续向$n的$l击出",
"$N右手化掌，「采手冲捶」向前圈采而出，又顺势拉回右手，将左拳向$n击出",
"$N右掌一拂而起，一招「推窗望月」，左掌自侧面连消带打，登时将$n的力道带斜，右掌一挥，拍向$p$l",
"$N使一招「分水擒龙」，右臂突伸抓向$n，左掌陡然沿着伸长的右臂，飞快的一削而出，斩向$n的$l",
"$N突然使一式「白云幻舞」，双臂如旋风一般一阵狂舞，刮起一阵旋转的气浪，掌势一推，压向$n",
"$N一招「掌中乾坤」，一掌拍出以后，猛地侧过身来，右臂自左肋下疾翻而出，拇，中两指扣圈猛弹$n的$l",
"$N一招「落日赶月」，伸掌一拍一收，一拍无丝毫力道，一收之间，一股阴柔无比的力道才陡然发出",
"$N一招「天罗地网」，左掌大圈而出，右掌小圈而出，两股奇异的力道一会之下，巨大的内劲压向$n的$l",
"$N一招「五指幻山」，猛一吐气，单掌有如推门，另一掌却是迅疾无比的一推即收，双劲合一，去势如虎",
"$N大喝一声，双掌交错，若有若无，飘渺间一招「金玉满堂」，掌风急速拍向$n的$l",
"$N一招「斜步插花」微向右转，成独立步站定，同时右手化掌向$n探抓",
"$N左手由右掌上方直穿而出，这招「左穿云手」直插$n的$l",
"$N右手由左掌上方直穿而出，一招「右穿云手」插向$n的$l",
"$N成丁字步，「落步盘花」 左拳极力向上反穿而出，接著收回右掌，向下击落",
"$N出一招「翻身平掌」，全身向左转正，左手化刁手，右手以横切掌向$n直切而出",
"$N一招「走马活挟」，左右手同时以穿云手向$n穿出，连环三式",
"$N一式「回马横擂」，左腿向前踢出双飞腿，同时左手回勾，右手前穿拍向$n",
"$N左手圈封而回护住右肩，一招「翻天劈地」右手以钻拳向$n穿打而出",
"$N右腿向前以小扫腿向前扫出，双手握拳「泰山压顶」直压向$n的$l",
"$N出「回步双切」，身体後仰，双手同时向前双抄而上，打向$n的$l",
"$N身体右倾，一招「反身插花」，左掌不动，右掌向右下方反切$n$l",
"$N一式「翻天双风」，双手以双抄掌向前反切而出，於面前硬碰，发出声音",
"$N左刁手不动，右掌收回胸前续劲，「顺势推山」以立掌向$n直推而出",
"$N收回双手，以十字手封住胸前，「拗步听风」接着双掌向$n平撑而出",
"$N一式「走回马枪」，双手右甩，左手护肩，右手极力下甩又直挑而上"
});

string *super_msg = ({
"$N身行暴起，一式「蛰雷为动」，双掌横横切出，掌缘才递出，呜呜呼啸之声狂作，铁掌之名，由此而出",
"$N突然大吼一声，身行疾飞而起，双掌翻飞，巨灵般的掌力猛向$n直扑而下，空气中暴出“呜”的一声刺耳尖啸！",
"$N凝力双掌，顺势朝前推去，竟然出现一只巨大的手掌，直轰$n$l",
"$N双掌顺势一摆，一道罡气破空而出",
});
int valid_enable(string usage)
{
        return usage== "strike" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        int level;
        string msg;
        level = (int)me->query_skill("super-strike",1);
        
        if(me->query_temp("tz/heyi")){
           	switch(me->query_temp("tz/heyi")){
            		case 2: msg = HIG"紧接着$N身体一转，到了$n身旁，左掌顺力拍出，这一招看似平和，实是内涵罡气，威力无比！"NOR;break;
            		case 1: msg = CYN"$N突然脚下一晃，欺进$n，右掌一翻，运起铁掌罡气，单掌向$p顶门直拍而下！"NOR; break;
           	}  
           	me->add_temp("tz/heyi", -1);
           	return ([
                        "action":msg, 
                        "force" :level + me->query("jiali"),
                        "dodge": random(30)+random(30),
                        "damage": level/2,
                        "parry": 20+random(20),
                        "damage_type" : "内伤",
        	]);
        }
    	
    	if( level > 350
        && me->query_skill_prepared("strike") == "super-strike" 
        && me->query_skill_mapped("strike") == "super-strike"
	&& random(7)>4
)
    		return ([  
                	"action" : WHT +super_msg[random(sizeof(super_msg))]+NOR,
                	"force" :  level * 2,
                	"dodge":   level,
                	"parry":   level,
                	"weapon": "罡气",
     "damage": level * 2,
        	"damage_type" :random(2)==1?"内伤":"震伤",
        	]);
        if (!weapon)
       	 	return ([
                	"action":CYN +msgc[random(sizeof(msgc))]+NOR,
                	"damage_type":"内伤",
       "damage": random(level/3),
         	"dodge":random(me->query_dex() * 2),
                	"force":me->query_skill("force") + me->query_str() * 2 + me->query("jiali") * 2,
 "parry": random(me->query_con() * 2),
"weapon" : "罡气",
       	]);
}

int practice_skill(object me)
{
        if (!me->query("sg/tzjj"))
             return notify_fail("你没有得到上官帮主许可，怎么能偷学铁掌掌法。\n");        
        if (!me->query_skill("force", 1))
                if((int)me->query_skill("force", 1) < 100)
                        return notify_fail("你的内功火候不够，无法练铁掌掌法。\n");
        if ((int)me->query("jingli") < 70)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 30)
                return notify_fail("你的内力不够练铁掌掌法。\n");                         
        me->receive_damage("jingli", 40);
        me->receive_damage("neili", 10+random(10));
        return 1;
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练铁掌掌法必须空手。\n");
        if (!me->query("sg/tzjj"))
             return notify_fail("你没有得到上官帮主许可，怎么能偷学铁掌掌法。\n");
        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("你的内功火候不够，无法学铁掌掌法。\n");
        if ((int)me->query("max_neili") < 3000)
                return notify_fail("你的内力太弱，无法练铁掌掌法。\n");
        return 1;
}


int ob_hit(object ob, object me, int damage)
{
        string msg;
        int i, neili,p,j,skill, neili1;
        skill = me->query_skill("super-strike", 1);
        neili = me->query("neili");
        neili1 = ob->query("neili");

        if(!living(ob)) return damage;
        if(neili < 300) return damage; 
           msg = parry_msg[random(sizeof(parry_msg))];
             if(neili >= random(neili1)+damage){
              msg += "结果基本上卸掉了$n的力道。\n";              
              j = -(damage+skill);
              }
           else{
              j = damage/2+random(damage/2); 
              if(j<damage/2) msg += "结果卸掉了一些$n的力道。\n";
              else msg += "结果卸掉了$n一半的力道。\n";
              j = -j;
            }           
           message_vision(msg, me, ob);
           return j;
          
     
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{                
        if(random(me->query_skill("super-strike", 1)) > 100 &&
            me->query_skill("poison", 1) > 60) {                
            victim->apply_condition("tz_poison", random(6) + 
                    (me->query_skill("poison", 1)/10) +
                    victim->query_condition("tz_poison"));
        }
}

string perform_action_file(string action)
{
        return __DIR__"super-strike/" + action;
}
