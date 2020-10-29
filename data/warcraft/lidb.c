// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小心竹[2;37;0m[2;37;0m", ({"xxzq"}));        
        set("gender", "女性");                
        set("long", "魔兽[2;37;0m
它是炼才的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lidb");
        set("owner_name", "炼才");
        set_temp("owner", "lidb");
        set_temp("owner_name", "炼才");
        ::setup();
}
