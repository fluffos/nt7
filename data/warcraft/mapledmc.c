// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("无双马[2;37;0m[2;37;0m", ({"dmcp"}));        
        set("gender", "女性");                
        set("long", "无双马[2;37;0m
它是枫无双的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mapledmc");
        set("owner_name", "枫无双");
        set_temp("owner", "mapledmc");
        set_temp("owner_name", "枫无双");
        ::setup();
}
