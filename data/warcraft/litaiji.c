// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小猪[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "小猪[2;37;0m
它是李百的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "litaiji");
        set("owner_name", "李百");
        set_temp("owner", "litaiji");
        set_temp("owner_name", "李百");
        ::setup();
}
