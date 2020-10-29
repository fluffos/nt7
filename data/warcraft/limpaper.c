// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("二号[2;37;0m[2;37;0m", ({"tonya"}));        
        set("gender", "男性");                
        set("long", "二号[2;37;0m
它是咖啡二号的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "limpaper");
        set("owner_name", "咖啡二号");
        set_temp("owner", "limpaper");
        set_temp("owner_name", "咖啡二号");
        ::setup();
}
