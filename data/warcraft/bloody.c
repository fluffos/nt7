// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m炫舞星空[2;37;0m[2;37;0m", ({"turtle"}));        
        set("gender", "男性");                
        set("long", "炫舞星空[2;37;0m
它是满江红的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "bloody");
        set("owner_name", "满江红");
        set_temp("owner", "bloody");
        set_temp("owner_name", "满江红");
        ::setup();
}
