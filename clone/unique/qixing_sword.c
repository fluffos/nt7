// Copyright (C) 2003, by Lonely. All rights reserved. 
// This software can not be used, copied, or modified  
// in any form without the written permission from authors. 
// qixing-sword.c 七星龙渊
// for only one object in mud

#include <ansi.h>  
#include <weapon.h>  
inherit SWORD;  
inherit F_UNIQUE;  

void create() 
{
        set_name(HIC "七星龙渊" NOR, ({"qixing longyuan", "longyuan", "sword"}));  
        set_weight(15000);  
        /*if (clonep())  
                set_default_object(__FILE__);  
        else*/ {  
                set("unit", "把");  
                set("long", sort_msg(HIC "这把剑传说是由欧冶子和干将两大剑师联手所铸。欧冶子"
                                     "和干将为铸此剑，凿开茨山，放出山中溪水，引至铸剑炉旁成" 
                                     "北斗七星环列的七个池中，是名“七星”。剑成之后，俯视剑" 
                                     "身，如同登高山而下望深渊，飘渺而深邃仿佛有巨龙盘卧。是" 
                                     "名“龙渊”。此剑铸造的技艺固然精湛，但它的闻名还在于无" 
                                     "法知道其真实姓名的普通渔翁：鱼丈人。话说伍子胥因奸臣所" 
                                     "害，亡命天涯，被楚国兵马一路追赶，这一天荒不择路，逃到" 
                                     "长江之滨，只见浩荡江水，波涛万顷。前阻大水，后有追兵，" 
                                     "正在焦急万分之时，伍子胥发现上游有一条小船急速驶来，船" 
                                     "上渔翁连声呼他上船，伍子胥上船后，小船迅速隐入芦花荡中" 
                                     "，不见踪影，岸上追兵悻悻而去，渔翁将伍子胥载到岸边，为" 
                                     "伍子胥取来酒食饱餐一顿，伍子胥千恩万谢，问渔翁姓名，渔" 
                                     "翁笑言自己浪迹波涛，姓名何用，只称：“渔丈人”即可，伍" 
                                     "子胥拜谢辞行，走了几步，心有顾虑又转身折回，从腰间解下" 
                                     "祖传三世的宝剑：七星龙渊，欲将此价值千金的宝剑赠给渔丈" 
                                     "人以致谢，并嘱托渔丈人千万不要泄露自己的行踪，渔丈人接" 
                                     "过七星龙渊宝剑，仰天长叹，对伍子胥说道：搭救你只因为你" 
                                     "是国家忠良，并不图报，而今，你仍然疑我贪利少信，我只好" 
                                     "以此剑示高洁。说完，横剑自刎。伍子胥悲悔莫名。故事见于" 
                                     "《吴越春秋》。七星龙渊是一把诚信高洁之剑。\n" NOR));
                set("value", 100000);  
                set("material", "steel"); 
                set("no_sell", "我的天…你…你知道这是啥么？这你也敢拿来卖？");  
                set("unique", 1);  
                set("rigidity", 500);  
                set("replica_ob", "/clone/weapon/changjian"); 
                set("no_put",1);  
                set("no_steal",1); 
                set("wield_msg",HIC"$N[噌]的一声抽出一把七星龙渊。\n"NOR);  
                set("unwield_msg",HIC"$N把手中的七星龙渊插入剑鞘。\n"NOR);  
                } 
                init_sword(800);  
                setup(); 
} 

mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return HIC "七星龙渊剑身突然冒出一股刺水，攻象$n" 
               HIC "，$n只能硬着头皮抵挡。\n" NOR; 
} 