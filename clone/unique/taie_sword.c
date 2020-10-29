// Copyright (C) 2003, by Xlz. All rights reserved.   
// This software can not be used, copied, or modified    
// in any form without the written permission from authors.   
// tai-sword.c 泰
// for only one object in mud  

#include <ansi.h>   
#include <weapon.h> 
inherit SWORD;   
inherit F_UNIQUE; 
void create()    
{
        set_name(CYN "泰阿剑" NOR, ({"taie sword", "taie", "sword"})); 
        set_weight(15000); 
        /*if (clonep())   
                set_default_object(__FILE__);    
        else*/ { 
                set("unit", "把");    
                set("long", sort_msg(CYN"楚国的都城已被晋国的兵马围困了三年。晋国出兵伐楚，" 
                                     "是想得到楚国的镇国之宝：阿剑。世人都说，泰阿剑是欧冶子" 
                                     "和干将两大剑师联手所铸。但是两位大师却不这样认为，他们" 
                                     "说泰阿剑是一把诸侯威道之剑早已存在，只是无形、无迹，但" 
                                     "是剑气早已存于天地之间，只等待时机凝聚起来，天时、地利" 
                                     "、人和三道归一，此剑即成。晋国当时因为强大，晋王当然认" 
                                     "为自己最有资格得到这把宝剑，但是事与愿违，此剑却在弱小" 
                                     "的国铸成，出剑之时，剑身果然天然镌刻篆体“泰阿”二字，" 
                                     "可见欧冶、干将所言不虚晋王当然咽不下这口气，于是向楚王" 
                                     "索剑，楚王拒绝，于是晋王出兵伐楚，以索剑之名借机灭掉楚" 
                                     "国。兵力悬殊，楚国大部分城池很快陷落并且都城也被团团围" 
                                     "住，一困三年。城里粮草告罄，兵革无存，危在旦夕。这一天" 
                                     "，晋国派来使者发出最后通牒：如再不交剑，明天将攻陷此城" 
                                     "，到时玉石俱焚！楚王不屈，吩咐左右，明天自己要亲上城头" 
                                     "战敌，如果城破，自己将用此剑自刎，然后左右要拾得此剑，" 
                                     "骑快马奔到大湖，将此剑投入湖底，让泰阿剑永留楚国。第二" 
                                     "天拂晓，楚王登上城头，只见城外晋国兵马遮天蔽日，自己的" 
                                     "都城宛如汪洋之中的一叶扁舟，随时有倾灭危险。晋国兵马开" 
                                     "始攻城，呐喊声同山呼海啸，城破在即。楚王双手捧剑，长叹" 
                                     "一声：泰阿剑啊，泰阿剑，我今天将用自己的鲜血来祭你！于" 
                                     "是，拔剑出鞘，引剑直指敌军。匪夷所思的奇迹出现了：只见" 
                                     "一把磅礴剑气激射而出，城外霎时飞砂走石遮天蔽日，似有猛" 
                                     "兽咆哮其中，晋国兵马大乱。片刻之后，旌旗仆地，流血千里" 
                                     "，全军覆没这件事情过后，楚王召来国中智者风胡子问道：泰" 
                                     "阿剑为何会有如此之威？风胡子对楚王道：泰阿剑是一把威道" 
                                     "之剑，而内心之威才是真威，大王身处逆境威武不屈正是内心" 
                                     "之威卓越表现，正是大王的内心之威激发出泰阿剑的剑气之威" 
                                     "啊！见于《越绝书》。泰阿剑是一把威道之剑！\n"NOR));
        set("value", 100000);   
        set("material", "steel");   
        set("no_sell", "我的天…你…你知道这是啥么？这你也敢拿来卖？");   
        set("unique", 1);   
        set("rigidity", 500);
        set("replica_ob", "/clone/weapon/changjian");   
        set("no_put",1); 
        set("no_steal",1);  
        set("wield_msg",CYN"$N[噌]的一声抽出一把泰阿剑，只见一把磅礴剑气激射而出，霎时，飞砂走石遮天蔽日，"
                              "似有猛兽咆哮其中。\n"NOR);
        set("unwield_msg",CYN"$N把手中的泰阿剑插入剑鞘，天空恢复了平静。\n"NOR);  
        } 
        init_sword(850);
        setup(); 
}
mixed hit_ob(object me, object victim, int damage_bonus)  
{
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return CYN "泰阿剑[铛]一声响，剑身一出，飞砂走石遮天蔽日，"   
              CYN "$n吓的掉头想跑。\n" NOR;  
} 