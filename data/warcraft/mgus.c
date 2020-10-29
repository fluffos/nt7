// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("碎大石[2;37;0m[2;37;0m", ({"dst"}));        
        set("gender", "女性");                
        set("long", "碎大石[2;37;0m
它是贤者的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "mgus");
        set("owner_name", "贤者");
        set_temp("owner", "mgus");
        set_temp("owner_name", "贤者");
        ::setup();
}
