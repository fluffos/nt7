// /kungfu/skill/liaoyuan-spear.c
// liaoyuan-spear.c 燎原枪法
// wuyue(08,1,22)
// wuyue(08.1.23)
#include <ansi.h>
#include <combat.h>
inherit SKILL;

mapping *action = ({
([
"action":"$N跃在半空，一招「大鹏展翅」，手中$w已化成无数枪影，令$n眼花缭乱，不知所措，连连倒退",
         "force" : 180,
         "dodge" : 20,
         "parry" : 20,
        "damage": 20,
         "lvl" : 0,
         "skill_name" : "大鹏展翅",
         "damage_type":"刺伤"
]),
([
"action":"$N挺$w将$n的招式架住，顺势一招「走马回枪」，$w上下左右飞快搅动，身随枪走，向$n压了下来",
         "force" : 200,
         "dodge" : 10,
         "parry" : 15,
        "damage": 100,
         "lvl" : 30,
         "skill_name" : "走马回枪",
         "damage_type":"刺伤"
]),
([
"action":"$N使一招「迎门三不过」，手中$w连续刺向$n面门，哽嗓，前心",
         "force" : 220,
         "dodge" : 15,
         "parry" : 20,
        "damage": 40,
         "lvl" : 60,
         "skill_name" : "迎门三不过",
         "damage_type":"刺伤"
]),
([
"action":"$N一个跨步，使一招「高山流水」，手中$w势若飞瀑刺向$n的$l",
         "force" : 240,
         "dodge" : 20,
         "parry" : 25,
        "damage": 60,
         "lvl" : 80,
         "skill_name" : "高山流水",
         "damage_type":"刺伤"
]),
([
"action":"$N一招「九莲宝灯」，身形如电，绕着$n飞快奔跑，手中$w一招快似一招，刹那间向$n连打出三十六枪",
         "force" : 280,
         "dodge" : 30,
         "parry" : 30,
        "damage": 80,
         "lvl" : 100,
         "skill_name" : "九莲宝灯",
         "damage_type":"刺伤"
]),
([
"action":
"$N一按枪把，一招「野火燎原」抖出五朵枪花。上下左右，虚虚实实刺向$n全身要害",
         "force" : 260,
         "dodge" : 30,
         "parry" : 40,
        "damage": 100,
         "lvl" : 120,
         "skill_name" : "野火燎原",
         "damage_type":"刺伤"
]),
([
"action":"$N大喝一声，一招「飞龙在天」，$w脱手飞出，夹着劲风射向$n的前心，随即抢到$n的身后，伸手又把$w抄在手中",
         "force" : 300,
         "dodge" : 20,
         "parry" : 30,
        "damage": 80,
         "lvl" : 130,
         "skill_name" : "飞龙在天",
         "damage_type":"刺伤"
]),
([
"action":"$N使一招「风扫梅花」，身体不停地旋转，右手$w随身转动，风雷电掣般向$n的$l扫去",
         "force" : 300,
         "dodge" : 20,
         "parry" : 30,
        "damage": 80,
         "lvl" : 130,
         "skill_name" : "风扫梅花",
         "damage_type":"砸伤"
]),
([
"action":"$N回身拧腰，右手虚握，一招「拨云瞻日」，$w中宫直进，中正平和地刺向$n的$l",
         "force" : 350,
         "dodge" : 20,
         "parry" : 30,
        "damage": 120,
         "lvl" : 130,
         "skill_name" : "拨云瞻日",
         "damage_type":"刺伤"
]),
([
"action":"只见$N一个斜跨，使个「举火烧天势」，手中$w带出一道寒气，由下而上疾挑$n$l",
         "force" : 350,
         "dodge" : 20,
         "parry" : 30,
        "damage": 100,
         "lvl" : 150,
         "skill_name" : "举火烧天势",
         "damage_type":"刺伤"
]),
});

string *parry_msg = ({
"$N持枪斜引，长枪横过，使$n竟无出招之处。\n",
"$N手中长枪斜指，往$n身前一搭，结果$n的力道被卸在一旁！",
"$N双手交错，持枪划了两个圆圈，罡气护住全身，竟无半分空隙，将$n之来势化解与无形。\n",
"只见$N使出四两拨千斤之巧劲，长枪斜引，将$n的攻击引在一旁！\n",
"$N以数十招枪法混成守势，似有千百柄长枪护住全身，圆转如意，竟无半分破绽。\n",
"$n身形绕向$N背后，$N身随枪转，反手圈转轻易地化解！\n"
});

string *msg = ({
HIG"$N神情萧索，一式「野火燎原」右手长枪扬手挥洒，虚实不定"NOR,
MAG"但见$N枪法吞吐开合、阴阳动静，实已到了草木为兵的绝诣"NOR,
HIW"$N手中$w"HIW"虽使得极快，却丝毫听不到金刃劈风之声，足见枪劲之柔韧已达于化境"NOR,
HIC"$N不疾不徐的漫步扬长而步，遇到$n招数，$N$w"HIC"一颤，便是一缕金光闪出"NOR,
HIC"$N凝望$n招式，出枪以蜿蜒之势、身处庄稳之形，宛如旭日东升，如金蛇万道，闪烁不定"NOR,
HIB"$N枪法突变，招式凌厉狠辣，以极浑厚内力，出极精妙招数，青光荡漾"NOR,
CYN"$N$w随手一招打出，以己之钝，挡敌之无锋"NOR,
HIC"$N猛然攻出招，招招都未曾使老，走势犹如浪潮一般，缓缓涌向$n"NOR,
MAG"$N$w"MAG"在空中划成大圈，右手戳出，竟似也发出嗤嗤微声"NOR,
HIW"$N一枪刺到，青光闪闪，发出嗤嗤声响，内力极强"NOR,
HIW"$N左手$w"HIW"不住的抖动，罩向$n上盘七大要穴，枪尖急颤，看不出攻向何处"NOR,
MAG"$N功劲一加运开，手中$w"MAG"枪势绵绵不绝，绝无破绽"NOR,
CYN"$N手里$w"CYN"使得心应手，熟极而流，招数精奇，轻翔灵动，变幻不测，突然抖腕直向$n的$l刺到"NOR,
HIW"$N以意驭枪，千变万化，无穷无尽，每一招都看似平淡，实则蓄势以待，深藏不露"NOR,
HIB"$N以意驭枪，绵绵不绝，看似柔软无力，实则千变万化，无穷无尽"NOR,
HIB"$N朗声长啸，枪法纵横变化，奇幻无方，$w"HIB"在其内力运使之下青光闪闪，威不可挡"NOR,
HIC"$N心中竟无半点渣滓，以意运枪，$w"HIC"每发一招，便有一道青光射向$n"NOR,
HIR"$N枪法吞吐开合、阴阳动静，将无招胜有招中最精要之处都发挥了出来，功劲一加运开，绵绵不绝"NOR,
HIR"$N左手$w"HIR"缓缓向前划出，成一弧形。$n只觉一股森森寒气，直逼过来"NOR,
CYN"$N左手$w"CYN"不住抖动，突然平刺，枪尖急颤，看不出攻向何处。$N这一招中笼罩了$n上盘七大要穴"NOR,
HIW"$N招数未曾使老，已然圈转。突然之间，$n眼前出现了几个白色光圈，大圈小圈，正圈斜圈，闪烁不已"NOR,
});

int valid_enable(string usage) { return  (usage == "spear") || (usage =="parry"); }

int valid_learn(object me)
{
        if (!me->query("sg/tzjj"))
             return notify_fail("你没有得到上官帮主许可，怎么能偷学燎原枪法。\n");
         if ((int)me->query("max_neili") < 1500)
                return notify_fail("你的内力不够。\n");
         if ((int)me->query_skill("force", 1) < 160)
                return notify_fail("你的内功火候太浅。\n");
         if((int)me->query_skill("spear",1) <=120)
      		return notify_fail("你的基本枪法火候不足，难以领悟燎原枪法。\n");
         return 1;
}
 
string perform_action_file(string action)
{
        return __DIR__"liaoyuan-spear/" + action;
}
string query_skill_name(int level)
{
         int i;
         for(i = sizeof(action)-1; i >= 0; i--)
                 if(level >= action[i]["lvl"])
                         return action[i]["skill_name"];
}

int double_attack(object me)
{	
        return 1;
   	if ( me->query_skill("liaoyuan-spear", 1) >= 80
     	&& me->query_skill_mapped("spear") == "liaoyuan-spear"
     	&& me->query("zhou/hubo"))
             	return 1;
}

mapping query_action(object me, object weapon)
{
         int i, level, lvl;
         object target;
	string msg1;
         mapping pre;
         string *skill, a, b;
         
         level   = (int) me->query_skill("liaoyuan-spear",1);
         lvl = (int)me->query_skill("super-strike", 1);
    
        if (random(me->query_skill("spear", 1)) > 100 
        && random(me->query_skill("liaoyuan-spear", 1)) > 100 
        && me->query_skill("force") > 100
	&& random(10)>6
        && me->query("neili") > 30 ) {
                me->add("neili", -20);
                return ([
 			"action": HIG"$N浑身看似破绽百出，$n却觉得无处下手，不经意间$N手中"+weapon->query("name")+""HIG"虚刺几下，$n一不留神就被$N一击命中。"NOR,
                  	"force": level+level/2+level/3,
                  	"parry": level+level/4,
                  	"dodge": level+level/4,
                  	"damage": level+level/2,
                  	"damage_type": "刺伤"
                ]);
        }
    
            if(me->query_temp("canyun"))
			{
				switch(me->query_temp("canyun"))
				{
				case 2: msg1 = HIY"$N出招稳凝如山，似乎其中破绽百出，手忙脚乱，其实似守实攻，大巧若拙，每一处破绽中都隐伏着厉害无比的陷阱。"NOR; break;
				case 1: msg1 = HIR"$N眼见对方已陷入重围，再也不能全身而退，当下持枪回击，陡然圈转，呼的一响，往$n$l上击了下去。"NOR; break;
				default: msg1 = HIW"$N突然大喝一声，纵身而上，手中$w"HIW"犹如狂风骤雨，使出「风卷残云」，漫天枪影带着气浪有如怒海狂滔一般！"NOR;break;
				}
				me->add_temp("canyun", -1);      
				return ([
                        "action":msg1, 
                        "force" : level+level/3,
                        "dodge":level+level/3 ,
  "damage":level ,
                        "parry": level/2,
                        "damage_type" : "刺伤",
              ]);
            }
    
        if (me->query_temp("slbw")) { 
  me->delete_temp("slbw");             
                return ([  
                        "action" : HIC"但见$N硬接了$n这一招，执枪紧接着向后一摆，一招「神龙摆尾」出其不意地点在了$n的$l上！"NOR,
                        "force":level+level/2,
                        "dodge": level/2,
  "damage":level+level/2 ,
                        "parry": level/2,
                        "damage_type" : "刺伤",
                        ]);
                }

 if( level > 350 ){   
        	if( weapon ){
        		switch(weapon->query("material")){
    				case "wood":
    				case "bamboo": 
    				case "paper":
        				weapon->set_temp("no_weapon_cut", 1); break;
        			default: break;
 }
}
        
        if( level > 450){
  return ([
                        "action":msg[random(sizeof(msg))],
   "damage":level + level/6,
                        "damage_type":"刺伤",
                        "dodge": level/2,
                	"parry":   level/2,
                        "force":level+random(level/2)
                ]);
        }
        
        if( level > 350
	&& random(10)>6){
  return ([
                        "action":msg[random(sizeof(msg))],
                        "damage":level + level/16,
                        "damage_type":"刺伤",
                        "dodge": level/5,
                	"parry":   level/5,
                        "force":level+random(level/5)
                ]);
        }
 }         
         if ( level >= 200 && lvl >= 200 && random(level) > lvl / 2
         && objectp(target = me->select_opponent())
         && objectp(weapon = me->query_temp("weapon"))
         && me->query_skill_mapped("strike") == "super-strike" 
         && me->query_skill_prepared("strike") == "super-strike" 
         && me->query("neili") > 300 && me->query("jingli") > 100 ) {
         	pre = me->query_skill_prepare();
        	skill = keys(pre);     
        	for (i=0; i<sizeof(skill); i++){
                	if(skill[i]=="strike") continue; 
                	a = skill[i];
                	b = pre[skill[i]];
                	me->prepare_skill(skill[i]);
        	}
        	
                weapon->unequip();
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
                weapon->wield();
                me->prepare_skill(a,b);
                me->add("neili", -15);
                me->add("jingli", -10);
         }
        


         for(i = sizeof(action); i > 0; i--)
                 if(level >= action[i-1]["lvl"])
                         return action[NewRandom(i, 20, level/5)];
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
    	object weapon, weapon1;
    	int i;    
    	weapon = me->query_temp("weapon");
    	weapon1= victim->query_temp("weapon");

	if( !objectp(weapon) ) return;
	i = me->query_skill("liaoyuan-spear", 1);
	
    	if(weapon1 && me->query("jiali")
       	&& me->query("max_neili") > 1200 && me->query("neili") > 1000 && random(10) >= 7
       	&& random(me->query_str()) > 30 
       	&& me->query_skill_mapped("parry") == "liaoyuan-spear"
       	&& random(me->query("combat_exp")) > victim->query("combat_exp")/4){
      		message_vision(HIM"$N持枪斜引，"+weapon->name()+HIM"平搭在$n"+weapon1->name()+HIM"背脊上，劲力传出，"+weapon1->name()+HIM"登时一沉！\n"NOR, me,victim);
      		if(random(me->query("str")) > victim->query("str")/3){           
           		me->add("neili", -50);
           		message_vision(HIR"$N招式渐见涩滞，只觉得手中"+weapon1->name()+HIR"不断的在增加重量，一个把持不定，脱手飞出！\n"NOR, victim);
           		weapon1->unequip();
           		weapon1->move(environment(victim));
           	}
      		else {
           		message_vision(HIY"$N一招使出，真力运得不足，被"+weapon->name()+HIY"带着连转几个圈子，手中"+weapon1->name()+HIY"一震，险些脱手！\n"NOR, victim);
           		victim->add_busy(3);
           	}
    	}
    	
    	else if( i > 350 ){
    		if( i < 350 ) return i/5;
    		switch(weapon->query("material")){
    			case "wood":
    			case "bamboo": 
    			case "paper":
    					if( random(i) > 250 
    					&& !victim->query_temp("lost_attack") 
   && random(me->query_str()+me->query_con()) > random(victim->query_int()*2) 
	&& random(10)>6){
    						victim->add_temp("lost_attack", 1+random(3));
    						message_vision(HIC"$P越斗越害怕，被$p带得招式渐见涩滞！\n"NOR, victim, me);
    						i *= 2;
    					}
    					
    					if( i > 450 ) i *= 2;
    				 	i += me->query_skill("force") * 2 + (me->query("jiali") * (10+random(10)));
    					break;
    			default: 	
    					if( i > 450 ) {
    						if( random(i) > 250 
    						&& !victim->query_temp("lost_attack") 
   && random(me->query_str()+me->query_con()
	&& random(10)>6) > random(victim->query_int()*2) ){
    							victim->add_temp("lost_attack", 1+random(3));
    							message_vision(HIC"$P越斗越害怕，被$p带得招式渐见涩滞！\n"NOR, victim, me);
    							i += random(i);
    						}
    						i *= 2;
    				 		i += me->query_skill("force") * 2 + (me->query("jiali") * (10+random(10)));
    						break;
    					}
}
}

        if(random(me->query_skill("liaoyuan-spear", 1)) > 100 &&
            me->query_skill("poison", 1) > 60) {      
            victim->apply_condition("hot_poison", random(6) + 
                    (me->query_skill("poison", 1)/10) +
                    victim->query_condition("hot_poison"));
        }
}


int ob_hit(object ob, object me, int damage)
{
        string msg;
        int i, neili,p,j,skill, neili1;
        skill = me->query_skill("liaoyuan-spear", 1);
        neili = me->query("neili");
        neili1 = ob->query("neili");

        if(!living(ob)) return damage;
        if(neili < 300) return damage;
        if(living(me) &&
        userp(me) &&
        random(me->query_str()) > ob->query_str()/4 &&
        random(me->query("combat_exp")) > ob->query("combat_exp")/10 &&
        me->query_skill("liaoyuan-spear", 1) >= 180 && 
        me->query("neili") > 600 &&
        !me->query_temp("slbw_hit") &&
        !ob->query("env/invisibility"))
        {
                me->set_temp("slbw", 1);
              i = me->query("jiali");
                neili = me->query("neili");
  me->set("jiali", me->query_skill("force") + 100);
        me->add_temp("apply/attack", me->query_skill("liaoyuan-spear", 1));
                me->add_temp("apply/strength", i/2);
            
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);
                
                if(me->query("neili") < neili) me->set("neili", neili-100);
                me->set("jiali", i);
                me->add_temp("apply/attack", -me->query_skill("liaoyuan-spear", 1));
                me->add_temp("apply/strength", -i/2);
        }else{       
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
           }           
           message_vision(msg, me, ob);
           return j;
          
     
}

int practice_skill(object me)
{
         object weapon;
         if((int)me->query_skill("spear",1) <=120)
      		return notify_fail("你的基本枪法火候不足，难以领悟燎原枪法。\n");
        if (!me->query("sg/tzjj"))
             return notify_fail("你没有得到上官帮主许可，怎么能偷学燎原枪法。\n");
         if (!objectp(weapon = me->query_temp("weapon"))
                  || (string)weapon->query("skill_type") != "spear")
                return notify_fail("你使用的武器不对。\n");
         if ((int)me->query("jingli") < 70)
                return notify_fail("你的体力不够练燎原枪法。\n");
         if ((int)me->query("neili") < 40)
                return notify_fail("你的内力不够练燎原枪法。\n");
                
 me->receive_damage("jingli", 30);           
         if((int)me->query_skill("liaoyuan-spear",1)> 200)
 me->add("neili",-10);

         return 1;
}

int help(object me)
{
	write(HIC"\n燎原枪法："NOR"\n");
	write(@HELP
	燎原枪法为三国时五虎将之赵云所创。此枪法乃赵云集百家之常，另
	辟捷径，常使人防不胜防！赵云争战数十年后，遇见各路枪法高手，不断总
	结，终于在晚年创出了此枪法，可以称的上天下第一枪法！不过后来不知流
	路何处，竟被上官剑南晚年在被囚山洞中所得！
	
HELP
	);
	return 1;
}

