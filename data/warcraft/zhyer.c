// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大鸟[2;37;0m[2;37;0m", ({"niao"}));        
        set("gender", "男性");                
        set("long", "人死鸟朝天，不死万万年。[2;37;0m
它是下雨的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zhyer");
        set("owner_name", "下雨");
        set_temp("owner", "zhyer");
        set_temp("owner_name", "下雨");
        ::setup();
}
