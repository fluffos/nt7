// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m宝马[2;37;0m[2;37;0m", ({"ricc"}));        
        set("gender", "男性");                
        set("long", "$HIW$宝马[2;37;0m
它是权葬的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ric");
        set("owner_name", "权葬");
        set_temp("owner", "ric");
        set_temp("owner_name", "权葬");
        ::setup();
}
