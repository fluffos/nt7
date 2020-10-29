// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// xuanyuan-sword.c 轩辕夏禹 
// for only one object in mud 

#include <ansi.h> 
#include <weapon.h> 
inherit SWORD; 
inherit F_UNIQUE; 

void create() 
{ 
        set_name(HIR "轩辕夏禹" NOR, ({"xuanyuan sword", "xuanyuan", "sword"})); 
        set_weight(15000); 
        /*if (clonep()) 
                set_default_object(__FILE__); 
        else*/ { 
                set("unit", "把"); 
                set("long", sort_msg(HIR "众神采首山之铜为黄帝所铸，后传与夏禹。在剑身一面刻"
                                     "有日月星辰，一面刻有山川草木。柄一面书农耕畜养之术，一"
                                     "面书四海一统之策。轩辕夏禹剑！对这一把剑还能些什么呢？"
                                     "黄帝、夏禹！对这样两个人我们还能说些什么呢。勇气、智慧"
                                     "、仁爱，一切在于两个字：圣道。轩辕夏禹剑是一把圣道之剑"
                                     "。\n" NOR));
                set("value", 100000); 
                set("material", "steel");
                set("no_sell", "我的天…你…你知道这是啥么？这你也敢拿来卖？"); 
                set("unique", 1); 
                set("rigidity", 500); 
                set("replica_ob", "/clone/weapon/changjian");
                set("no_put",1); 
                set("no_steal",1);   
                set("wield_msg",HIR"$N[噌]的一声抽出一把轩辕夏禹，漫天乌云，杀气四溅。\n"NOR); 
                set("unwield_msg",HIR"$N把手中的轩辕夏禹插入剑鞘，乌云速散，杀气顿无。\n"NOR); 
        }
        init_sword(1000); 
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return HIM "轩辕夏禹夹带着刺耳的破空声划出一道道长虹，霎时间$n"
               HIM "只感到心神意乱。\n" NOR;
}