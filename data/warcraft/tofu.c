// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("云逐风[2;37;0m[2;37;0m", ({"wincloud"}));        
        set("gender", "男性");                
        set("long", "无[2;37;0m
它是谢古的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tofu");
        set("owner_name", "谢古");
        set_temp("owner", "tofu");
        set_temp("owner_name", "谢古");
        ::setup();
}
