// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("太古[2;37;0m[2;37;0m", ({"armorblong"}));        
        set("gender", "男性");                
        set("long", "握草[2;37;0m
它是麒麟甲的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "armorb");
        set("owner_name", "麒麟甲");
        set_temp("owner", "armorb");
        set_temp("owner_name", "麒麟甲");
        ::setup();
}
