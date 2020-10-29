// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"moto"}));        
        set("gender", "女性");                
        set("long", "这是木大哥的专属坐骑[2;37;0m
它是沐大哥的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "mudlet");
        set("owner_name", "沐大哥");
        set_temp("owner", "mudlet");
        set_temp("owner_name", "沐大哥");
        ::setup();
}
