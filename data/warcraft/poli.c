// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"poe"}));        
        set("gender", "女性");                
        set("long", "das[2;37;0m
它是破黎的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "poli");
        set("owner_name", "破黎");
        set_temp("owner", "poli");
        set_temp("owner_name", "破黎");
        ::setup();
}
