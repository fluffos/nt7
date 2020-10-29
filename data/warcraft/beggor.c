// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m镊子[2;37;0m[2;37;0m", ({"niezi"}));        
        set("gender", "男性");                
        set("long", "拾荒用的镊子[2;37;0m
它是时荒的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "beggor");
        set("owner_name", "时荒");
        set_temp("owner", "beggor");
        set_temp("owner_name", "时荒");
        ::setup();
}
