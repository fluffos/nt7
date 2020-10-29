// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("爱疯[2;37;0m[2;37;0m", ({"iphone"}));        
        set("gender", "女性");                
        set("long", "这是一台爱疯的五色版本，这个有富贵金[2;37;0m
它是乔布斯的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ios");
        set("owner_name", "乔布斯");
        set_temp("owner", "ios");
        set_temp("owner_name", "乔布斯");
        ::setup();
}
