// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("鼠[2;37;0m[2;37;0m", ({"goldaaa"}));        
        set("gender", "男性");                
        set("long", "鼠[2;37;0m
它是金鼠的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldaa");
        set("owner_name", "金鼠");
        set_temp("owner", "goldaa");
        set_temp("owner_name", "金鼠");
        ::setup();
}
