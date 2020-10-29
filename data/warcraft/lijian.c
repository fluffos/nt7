// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m龙[2;37;0m[2;37;0m", ({"qlong"}));        
        set("gender", "男性");                
        set("long", "为剑而生 为剑而死[2;37;0m
它是钟离剑的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lijian");
        set("owner_name", "钟离剑");
        set_temp("owner", "lijian");
        set_temp("owner_name", "钟离剑");
        ::setup();
}
