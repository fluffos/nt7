// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("书架[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "书架[2;37;0m
它是宝石砂的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "gems");
        set("owner_name", "宝石砂");
        set_temp("owner", "gems");
        set_temp("owner_name", "宝石砂");
        ::setup();
}
