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
        set_name(HIR "承影" NOR, ({"chengying sword", "chengying", "sword"})); 
        set_weight(15000); 
        /*if (clonep()) 
                set_default_object(__FILE__); 
        else*/ { 
                set("unit", "把"); 
                set("long", sort_msg(HIR "远古的一个黎明，天色黑白交际的一瞬间，一双手缓缓扬起。双手合握之中"
                                     "是一截剑柄，只有剑柄不见长剑剑身，但是，在北面的墙壁上却隐隐投下一个飘"
                                     "忽的剑影，剑影只存片刻，就随着白昼的来临而消失，直到黄昏，天色渐暗，就"
                                     "在白昼和黑夜交错的霎那，那个飘忽的剑影又再次浮现出来。扬起的双手划出一"
                                     "条优雅的弧线，挥向旁边一棵挺拔的古松，耳廓中有轻轻的“嚓”的一声，树身微"
                                     "微一震，不见变化，然而稍后不久，翠茂的松盖就在一阵温和掠过的南风中悠悠"
                                     "倒下，平展凸露的圈圈年轮，昭示着岁月的流逝。天色愈暗，长剑又归于无形，"
                                     "远古的暮色无声合拢，天地之间一片静穆。这把有影无形的长剑就是在《列子。"
                                     "汤问》之中被列子激赏的铸于商朝后来被春秋时卫国人孔周所藏的名剑：承影。\n" NOR));
                                     
                set("value", 100000); 
                set("material", "steel");
                set("no_sell", "我的天…你…你知道这是啥么？这你也敢拿来卖？"); 
                set("unique", 1); 
                set("rigidity", 500); 
                set("replica_ob", "/clone/weapon/changjian");
                set("no_put",1); 
                set("no_steal",1);   
                set("wield_msg",HIR"$N[噌]的一声抽出一把承影，漫天乌云，杀气四溅。\n"NOR); 
                set("unwield_msg",HIR"$N把手中的承影入剑鞘，乌云速散，杀气顿无。\n"NOR); 
        }
        init_sword(500); 
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return HIM "承影夹带着刺耳的破空声划出一道道长虹，霎时间$n"
               HIM "只感到被优雅的气势所迷住。\n" NOR;
}