// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m洪安通万岁[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "$HIG$洪安通万岁[2;37;0m
它是希望的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "hopeso");
        set("owner_name", "希望");
        set_temp("owner", "hopeso");
        set_temp("owner_name", "希望");
        ::setup();
}
