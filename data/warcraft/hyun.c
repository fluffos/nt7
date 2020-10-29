// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大猫[2;37;0m[2;37;0m", ({"bigcat"}));        
        set("gender", "男性");                
        set("long", "大猫[2;37;0m
它是幻云的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "hyun");
        set("owner_name", "幻云");
        set_temp("owner", "hyun");
        set_temp("owner_name", "幻云");
        ::setup();
}
