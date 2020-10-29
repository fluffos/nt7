// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("咪咪[2;37;0m[2;37;0m", ({"miao"}));        
        set("gender", "男性");                
        set("long", "喵喵喵[2;37;0m
它是康少的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ajiji");
        set("owner_name", "康少");
        set_temp("owner", "ajiji");
        set_temp("owner_name", "康少");
        ::setup();
}
