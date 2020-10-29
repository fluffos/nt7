// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蚊子[2;37;0m[2;37;0m", ({"ant"}));        
        set("gender", "男性");                
        set("long", "1111111111111[2;37;0m
它是武学世家的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "mmmm");
        set("owner_name", "武学世家");
        set_temp("owner", "mmmm");
        set_temp("owner_name", "武学世家");
        ::setup();
}
