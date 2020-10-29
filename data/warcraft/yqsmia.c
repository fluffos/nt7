// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老马[2;37;0m[2;37;0m", ({"laom"}));        
        set("gender", "女性");                
        set("long", "老马[2;37;0m
它是竹篱笆的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yqsmia");
        set("owner_name", "竹篱笆");
        set_temp("owner", "yqsmia");
        set_temp("owner_name", "竹篱笆");
        ::setup();
}
