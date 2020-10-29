// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"vow"}));        
        set("gender", "女性");                
        set("long", "青龙[2;37;0m
它是棂纹的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "oath");
        set("owner_name", "棂纹");
        set_temp("owner", "oath");
        set_temp("owner_name", "棂纹");
        ::setup();
}
