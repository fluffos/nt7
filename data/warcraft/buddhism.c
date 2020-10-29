// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m[5m佛印莲台[2;37;0m[2;37;0m[2;37;0m", ({"liantai"}));        
        set("gender", "男性");                
        set("long", "佛印莲台[2;37;0m
它是佛心的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "buddhism");
        set("owner_name", "佛心");
        set_temp("owner", "buddhism");
        set_temp("owner_name", "佛心");
        ::setup();
}
