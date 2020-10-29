// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("远古[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "女性");                
        set("long", "这是一只远古青龙。[2;37;0m
它是清清的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mooktian");
        set("owner_name", "清清");
        set_temp("owner", "mooktian");
        set_temp("owner_name", "清清");
        ::setup();
}
