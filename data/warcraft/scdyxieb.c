// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火火火火麒麟[2;37;0m[2;37;0m", ({"xieb"}));        
        set("gender", "女性");                
        set("long", "一头火红的麒麟[2;37;0m
它是伯赏琨钰的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "scdyxieb");
        set("owner_name", "伯赏琨钰");
        set_temp("owner", "scdyxieb");
        set_temp("owner_name", "伯赏琨钰");
        ::setup();
}
