// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m大力神运输机[2;37;0m[2;37;0m", ({"plane"}));        
        set("gender", "男性");                
        set("long", "美制大力神运输机[2;37;0m
它是凯雷德的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "escalade");
        set("owner_name", "凯雷德");
        set_temp("owner", "escalade");
        set_temp("owner_name", "凯雷德");
        ::setup();
}
