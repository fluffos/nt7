// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("快快快[2;37;0m[2;37;0m", ({"xxll"}));        
        set("gender", "男性");                
        set("long", "快快快[2;37;0m
它是断溪水的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xxlowek");
        set("owner_name", "断溪水");
        set_temp("owner", "xxlowek");
        set_temp("owner_name", "断溪水");
        ::setup();
}
