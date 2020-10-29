// Copyright (C) 2003, by Xlz. All rights reserved. 
// This software can not be used, copied, or modified  
// in any form without the written permission from authors. 
// zhanlu-sword.c 湛
// for only one object in mud  

#include <ansi.h>  
#include <weapon.h>  
inherit SWORD;  
inherit F_UNIQUE;  

void create()  
{ 
        set_name(HIW "湛泸" NOR, ({"zhanlu sword", "zhanlu", "sword"}));  
        set_weight(15000);  
        /*if (clonep())  
                set_default_object(__FILE__);  
        else*/ {
                set("unit", "把");  
                set("long", sort_msg(HIW"湛泸是一把剑，更是一只眼睛。湛泸：湛湛然而黑色也" 
                                     "。这把通体黑色浑然无迹的长让人感到的不是它的锋利，而"
                                     "是它的宽厚和慈祥。它就象上苍一只目光深邃、明察秋的黑" 
                                     "色的眼睛，注视着君王、诸侯的一举一动。君有道，剑在侧" 
                                     "，国兴旺。君无道，剑飞弃，国破败。五金之英，太阳之精" 
                                     "，出之有神，服之有威。欧冶子铸成此剑时，不禁抚剑泪落" 
                                     "，因为他终于圆了自己毕生的梦想：铸出一把无坚摧而又不" 
                                     "带丝毫杀气的兵器。所谓仁者无敌，湛泸剑是一把仁道之剑。\n" NOR)); 
                set("value", 100000);  
                set("material", "steel"); 
                set("no_sell", "我的天…你…你知道这是啥么？这你也敢拿来卖？");  
                set("unique", 1);  
                set("rigidity", 500);  
                set("replica_ob", "/clone/weapon/changjian"); 
                set("no_put",1);  
                set("no_steal",1);
                set("wield_msg",HIW"$N[噌]的一声抽出一把湛泸，没有丝毫杀气。\n"NOR);  
                set("unwield_msg",HIW"$N把手中的湛泸插入剑鞘，剑身没有发出一丝声音。\n"NOR); 
        }
        init_sword(950); 
        setup(); 
}
mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return HIW "湛泸从$N手中飞向天空，[嗡]一声，湛泸从天空化做长虹回到了$N手中，$n" 
               HIW "只感到惊讶。\n" NOR; 
}