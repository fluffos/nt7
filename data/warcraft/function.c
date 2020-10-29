// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("贱人[2;37;0m[2;37;0m", ({"fun"}));        
        set("gender", "女性");                
        set("long", "贱人[2;37;0m
它是贱相的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "function");
        set("owner_name", "贱相");
        set_temp("owner", "function");
        set_temp("owner_name", "贱相");
        ::setup();
}
