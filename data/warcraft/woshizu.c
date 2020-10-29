// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("仲[2;37;0m[2;37;0m", ({"wiowe"}));        
        set("gender", "女性");                
        set("long", "去[2;37;0m
它是无很无的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "woshizu");
        set("owner_name", "无很无");
        set_temp("owner", "woshizu");
        set_temp("owner_name", "无很无");
        ::setup();
}
