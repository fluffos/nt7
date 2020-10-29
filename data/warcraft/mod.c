// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神龙[2;37;0m[2;37;0m", ({"kow"}));        
        set("gender", "女性");                
        set("long", "龙神[2;37;0m
它是新手之神的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mod");
        set("owner_name", "新手之神");
        set_temp("owner", "mod");
        set_temp("owner_name", "新手之神");
        ::setup();
}
