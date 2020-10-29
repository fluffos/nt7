// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("书架[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "书架[2;37;0m
它是老球球的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ovozl");
        set("owner_name", "老球球");
        set_temp("owner", "ovozl");
        set_temp("owner_name", "老球球");
        ::setup();
}
