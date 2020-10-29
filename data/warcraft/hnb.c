// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "女性");                
        set("long", "青龙[2;37;0m
它是好牛比的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hnb");
        set("owner_name", "好牛比");
        set_temp("owner", "hnb");
        set_temp("owner_name", "好牛比");
        ::setup();
}
