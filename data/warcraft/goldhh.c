// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("羊[2;37;0m[2;37;0m", ({"goldhhh"}));        
        set("gender", "男性");                
        set("long", "羊[2;37;0m
它是金羊的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldhh");
        set("owner_name", "金羊");
        set_temp("owner", "goldhh");
        set_temp("owner_name", "金羊");
        ::setup();
}
