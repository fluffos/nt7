// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("五花马[2;37;0m[2;37;0m", ({"omo"}));        
        set("gender", "女性");                
        set("long", "五花马[2;37;0m
它是周仓十的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xpc");
        set("owner_name", "周仓十");
        set_temp("owner", "xpc");
        set_temp("owner_name", "周仓十");
        ::setup();
}
