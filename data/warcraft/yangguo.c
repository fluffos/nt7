// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("天空[2;37;0m[2;37;0m", ({"tian"}));        
        set("gender", "男性");                
        set("long", "蓝蓝的天空[2;37;0m
它是杨过的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yangguo");
        set("owner_name", "杨过");
        set_temp("owner", "yangguo");
        set_temp("owner_name", "杨过");
        ::setup();
}
