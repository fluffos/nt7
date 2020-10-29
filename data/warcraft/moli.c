// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火[2;37;0m[2;37;0m", ({"huo"}));        
        set("gender", "男性");                
        set("long", "火[2;37;0m
它是墨璃的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "moli");
        set("owner_name", "墨璃");
        set_temp("owner", "moli");
        set_temp("owner_name", "墨璃");
        ::setup();
}
