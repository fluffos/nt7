// Copyright (C) 2003, by Lonely. All rights reserved. 
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// ganjiang-sword.c 干将
// for only one object in mud  

#include <ansi.h>  
#include <weapon.h>  
inherit SWORD;  
inherit F_UNIQUE;  

void create() 
{ 
        set_name(HIB "干将" NOR, ({"ganjiang sword", "ganjiang", "sword"})); 
        set_weight(15000);  
        /*if (clonep())  
                set_default_object(__FILE__);  
        else*/ {  
                set("unit", "把"); 
                set("long", sort_msg(HIB "干将、莫邪是两把剑，但是没有人能分开它们。干将、莫"
                                     "邪是两个人，同样，也没有人能将他（她）们分开。干将、莫"
                                     "邪是干将、莫邪铸的两把剑。干将是雄剑，莫邪是雌剑。干将"
                                     "是丈夫，莫邪是妻子。干将很勤劳，莫邪很温柔。干将为吴王"
                                     "铸剑的时候，莫邪为干将扇扇子，擦汗水。三个月过去了，干"
                                     "将叹了一口气。莫邪也流出了眼泪。莫邪知道干将为什么叹气"
                                     "，因为炉中采自五山六合的金铁之精无法熔化，铁英不化，剑"
                                     "就无法铸成。干将也知道莫邪为什么流泪，因为剑铸不成，自"
                                     "己就得被吴王杀死。干将依旧叹气，而在一天晚上，莫邪却突"
                                     "然笑了。看到莫邪笑了，干将突然害怕起来，干将知道莫邪为"
                                     "什么笑，干将对莫邪说：莫邪，你千万不要去做。莫邪没说什"
                                     "么，她只是笑。干将醒来的时候，发现莫邪没在身边。干将如"
                                     "万箭穿心，他知道莫邪在哪儿。莫邪站在高耸的铸剑炉壁上，"
                                     "裙裾飘飞，宛如仙女。莫邪看到干将的身影在熹微的晨光中从"
                                     "远处急急奔来。她笑了，她听到干将嘶哑的喊叫：莫邪，莫邪"
                                     "依然在笑，但是泪水也同时流了下来。干将也流下了眼泪，在"
                                     "泪光模糊中他看到莫邪飘然坠下，他听到莫邪最后对他说道："
                                     "干将，我没有死，我们还会在一起。铁水熔化，剑顺利铸成。"
                                     "一雄一雌，取名干将莫邪，干将只将“干将”献给吴王。干将"
                                     "私藏“莫邪”的消息很快被吴王知晓，武士将干将团团围住，"
                                     "干将束手就擒，他打开剑匣绝望地向里面问道：莫邪，我们怎"
                                     "样才能在一起？剑忽从匣中跃出，化为一条清丽的白龙，飞腾"
                                     "而去，同时，干将也突然消失无踪。在干将消失的时候，吴王"
                                     "身边的“干将”剑也不知去向。而在千里之外的荒凉的贫城县"
                                     "，在一个叫延平津的大湖里突然出现了一条年轻的白龙。这条"
                                     "白龙美丽而善良，为百姓呼风唤雨，荒凉的贫城县渐渐风调雨"
                                     "顺，五谷丰登，县城的名字也由贫城改为丰城。可是，当地人"
                                     "却时常发现，这条白龙几乎天天都在延平津的湖面张望，象在"
                                     "等待什么，有人还看到它的眼中常含着泪水。六百年过去了。"
                                     "一个偶然的机会里，丰城县令雷焕在修筑城墙的时候，从地下"
                                     "掘出一个石匣，里面有一把剑，上面赫然刻着“干将”二字，"
                                     "雷焕欣喜异常，将这把传诵已久的名剑带在身边。有一天，雷"
                                     "焕从延平津湖边路过，腰中佩剑突然从鞘中跳出跃进水里，正"
                                     "在雷焕惊愕之际，水面翻涌，跃出黑白双龙，双龙向雷焕频频"
                                     "点头意在致谢，然后，两条龙脖颈亲热地纠缠厮磨，双双潜入"
                                     "水底不见了。在丰城县世代生活的百姓们，发现天天在延平津"
                                     "湖面含泪张望据说已存在了六百多年的白龙突然不见了。而在"
                                     "第二天，县城里却搬来了一对平凡的小夫妻。丈夫是一个出色"
                                     "的铁匠，技艺非常精湛，但他只用心锻打挣不了几个钱的普通"
                                     "农具却拒绝打造有千金之利的兵器，在他干活的时候，他的小"
                                     "妻子总在旁边为他扇扇子，擦汗水。这是两把中的一把：干将。"
                                     "干将是一把挚情之剑。\n" NOR));
        set("value", 100000);  
        set("material", "steel"); 
        set("no_sell", "我的天…你…你知道这是啥么？这你也敢拿来卖？");  
        set("unique", 1);  
        set("rigidity", 500);  
        set("replica_ob", "/clone/weapon/changjian"); 
        set("no_put",1);  
        set("no_steal",1);    
        set("wield_msg",HIB"$N[噌]的一声抽出一把干将，干将似一条黑龙，象是等待着什么。\n"NOR);  
        set("unwield_msg",HIB"$N把手中的干将插入剑鞘。\n"NOR);  
     } 
     init_sword(750);  
     setup(); 
} 

mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return HIB "干将似一条黑龙一般咬向$n，" 
               HIB "$n只感到恐慌。\n" NOR; 
}