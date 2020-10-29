// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("镖旗[2;37;0m[2;37;0m", ({"xbiaoshia"}));        
        set("gender", "女性");                
        set("long", "这是一杆镖旗[2;37;0m
它是镖师一的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "biaoshia");
        set("owner_name", "镖师一");
        set_temp("owner", "biaoshia");
        set_temp("owner_name", "镖师一");
        ::setup();
}
