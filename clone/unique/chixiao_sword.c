// Copyright (C) 2003, by Xlz. All rights reserved.  
// This software can not be used, copied, or modified   
// in any form without the written permission from authors.  
// chi-sword.c 赤
// for only one object in mud   

#include <ansi.h>   
#include <weapon.h>   
inherit SWORD;   
inherit F_UNIQUE;   
void create()   
{ 
        set_name(HIR "赤霄剑" NOR, ({"chixiao sword", "chixiao", "sword"}));   
        set_weight(15000); 
        /*if (clonep())   
                set_default_object(__FILE__);   
        else*/ {
                set("unit", "把");   
                set("long", HIY "这是一把饰有七彩珠、九华玉的寒光逼人、刃如霜雪的宝剑。\n"
                                "这把剑就是斩蛇起义的赤霄剑，赤霄剑是一把帝道之剑。\n" NOR);
        set("value", 100000);  
        set("material", "steel");  
        set("no_sell", "我的天…你…你知道这是啥么？这你也敢拿来卖？");   
        set("unique", 1);     
        set("rigidity", 500);   
        set("replica_ob", "/clone/weapon/changjian");  
        set("no_put",1);
        set("no_steal",1); 
        set("wield_msg",HIR"$N[噌]的一声抽出一把赤剑，忽然从旁边跳出一条赤龙，围着$N转。\n"NOR);   
        set("unwield_msg",HIR"$N把手中的赤剑插入剑鞘，赤龙化做长虹飞到天空，消失了。\n"NOR);    
        } 
        init_sword(900);   
        setup();
}
mixed hit_ob(object me, object victim, int damage_bonus)  
{ 
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return HIR "赤剑[叮]一声响，霎那，那条赤龙张口就咬$n"  
               HIR "，$n只能冷冷做怕。\n" NOR; 
}