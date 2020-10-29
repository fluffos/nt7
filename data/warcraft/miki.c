// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("奇奇[2;37;0m[2;37;0m", ({"kimi"}));        
        set("gender", "女性");                
        set("long", "奇奇[2;37;0m
它是紫琪的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "miki");
        set("owner_name", "紫琪");
        set_temp("owner", "miki");
        set_temp("owner_name", "紫琪");
        ::setup();
}
