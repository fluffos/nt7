// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "女性");                
        set("long", "青龙[2;37;0m
它是江洪的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xyfh");
        set("owner_name", "江洪");
        set_temp("owner", "xyfh");
        set_temp("owner_name", "江洪");
        ::setup();
}
