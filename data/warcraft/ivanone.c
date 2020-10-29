// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("花麒麟[2;37;0m[2;37;0m", ({"huaqilin"}));        
        set("gender", "男性");                
        set("long", "一只花麒麟，就这样。[2;37;0m
它是艾文的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ivanone");
        set("owner_name", "艾文");
        set_temp("owner", "ivanone");
        set_temp("owner_name", "艾文");
        ::setup();
}
