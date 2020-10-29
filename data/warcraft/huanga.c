// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("夺要[2;37;0m[2;37;0m", ({"asdf"}));        
        set("gender", "男性");                
        set("long", "夺要[2;37;0m
它是大刀向东的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "huanga");
        set("owner_name", "大刀向东");
        set_temp("owner", "huanga");
        set_temp("owner_name", "大刀向东");
        ::setup();
}
