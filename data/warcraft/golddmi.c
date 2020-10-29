// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"zxcc"}));        
        set("gender", "男性");                
        set("long", "alias m whistle zxcc[2;37;0m
它是黄金鬼的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "golddmi");
        set("owner_name", "黄金鬼");
        set_temp("owner", "golddmi");
        set_temp("owner_name", "黄金鬼");
        ::setup();
}
