// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"que"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是阿珂的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cocoa");
        set("owner_name", "阿珂");
        set_temp("owner", "cocoa");
        set_temp("owner_name", "阿珂");
        ::setup();
}
