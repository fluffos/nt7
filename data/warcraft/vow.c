// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"vew"}));        
        set("gender", "女性");                
        set("long", "青龙[2;37;0m
它是柃纹的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "vow");
        set("owner_name", "柃纹");
        set_temp("owner", "vow");
        set_temp("owner_name", "柃纹");
        ::setup();
}
