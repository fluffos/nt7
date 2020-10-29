// This program is a part of NITAN MudLIB 
// redl 2013/10
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR YEL "六帝币" NOR, ({ "liudi bi", "bi", "liudi"}));
        set("long", NOR HIY
"六帝币包括中国清代盛世的六位皇帝\n"
"顺治、康熙、雍正、乾隆、嘉庆、道光，\n"
"各年间所铸造的铜钱和一块白色纯玉石用线串联而成。\n"
"眼前这一串六帝币却是纯金打造，有驱煞镇魔辟邪卫道之力。\n" NOR HIK
"( 一次性消费品，自动使用，效果等同于免去此次upg所需的材料 )\n" NOR);
        set_weight(100);
                set("unit", "串");
                set("value", 50000000);
                set("weight", 200);
                set("set_data", 1);  
                set("auto_load", 1);  
        setup();
}        

