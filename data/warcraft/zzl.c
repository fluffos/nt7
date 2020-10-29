// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("书架[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "书架[2;37;0m
它是球球的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zzl");
        set("owner_name", "球球");
        set_temp("owner", "zzl");
        set_temp("owner_name", "球球");
        ::setup();
}
