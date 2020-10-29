// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("瑞兽麒麟王[2;37;0m[2;37;0m", ({"nixingqilin"}));        
        set("gender", "男性");                
        set("long", "瑞兽麒麟王[2;37;0m
它是任性的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "rennixing");
        set("owner_name", "任性");
        set_temp("owner", "rennixing");
        set_temp("owner_name", "任性");
        ::setup();
}
