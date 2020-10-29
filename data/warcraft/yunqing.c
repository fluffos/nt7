// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m圣火令[2;37;0m[2;37;0m", ({"shenghuo"}));        
        set("gender", "男性");                
        set("long", "圣火令是明教的镇教圣物，似透明，非透明，令中隐隐有火焰飞腾。[2;37;0m
它是云卿的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yunqing");
        set("owner_name", "云卿");
        set_temp("owner", "yunqing");
        set_temp("owner_name", "云卿");
        ::setup();
}
