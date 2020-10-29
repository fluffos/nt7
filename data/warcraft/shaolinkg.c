// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是苦工头陀的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "shaolinkg");
        set("owner_name", "苦工头陀");
        set_temp("owner", "shaolinkg");
        set_temp("owner_name", "苦工头陀");
        ::setup();
}
