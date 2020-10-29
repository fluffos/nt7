// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"zxcc"}));        
        set("gender", "男性");                
        set("long", "自行车[2;37;0m
它是蒯风德的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "roewhqikf");
        set("owner_name", "蒯风德");
        set_temp("owner", "roewhqikf");
        set_temp("owner_name", "蒯风德");
        ::setup();
}
