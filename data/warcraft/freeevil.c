// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;35m激情[2;37;0m[1;31m澎湃[2;37;0m[2;37;0m", ({"fervour"}));        
        set("gender", "男性");                
        set("long", "激情澎湃[2;37;0m
它是刹那激情的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "freeevil");
        set("owner_name", "刹那激情");
        set_temp("owner", "freeevil");
        set_temp("owner_name", "刹那激情");
        ::setup();
}
