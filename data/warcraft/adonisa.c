// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大胖马[2;37;0m[2;37;0m", ({"www"}));        
        set("gender", "男性");                
        set("long", "大胖马[2;37;0m
它是阿多一的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "adonisa");
        set("owner_name", "阿多一");
        set_temp("owner", "adonisa");
        set_temp("owner_name", "阿多一");
        ::setup();
}
