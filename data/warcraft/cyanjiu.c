// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("兽性大发[2;37;0m[2;37;0m", ({"yanjiushou"}));        
        set("gender", "男性");                
        set("long", "兽性大发[2;37;0m
它是李十九的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cyanjiu");
        set("owner_name", "李十九");
        set_temp("owner", "cyanjiu");
        set_temp("owner_name", "李十九");
        ::setup();
}
