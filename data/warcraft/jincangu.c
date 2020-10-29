// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青青的[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "青青的[2;37;0m
它是金蚕蛊的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jincangu");
        set("owner_name", "金蚕蛊");
        set_temp("owner", "jincangu");
        set_temp("owner_name", "金蚕蛊");
        ::setup();
}
