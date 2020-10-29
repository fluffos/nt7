// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m老手导师[2;37;0m[2;37;0m", ({"daoshi"}));        
        set("gender", "女性");                
        set("long", "爽[2;37;0m
它是新手导师的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tutor");
        set("owner_name", "新手导师");
        set_temp("owner", "tutor");
        set_temp("owner_name", "新手导师");
        ::setup();
}
