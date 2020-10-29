// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"kuna"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是昆昆的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kun");
        set("owner_name", "昆昆");
        set_temp("owner", "kun");
        set_temp("owner_name", "昆昆");
        ::setup();
}
