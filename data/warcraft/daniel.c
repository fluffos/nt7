// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("天行者[2;37;0m[2;37;0m", ({"skywalker"}));        
        set("gender", "男性");                
        set("long", "一只朱雀[2;37;0m
它是高希的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "daniel");
        set("owner_name", "高希");
        set_temp("owner", "daniel");
        set_temp("owner_name", "高希");
        ::setup();
}
