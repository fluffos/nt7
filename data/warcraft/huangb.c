// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("夺工[2;37;0m[2;37;0m", ({"sasdf"}));        
        set("gender", "男性");                
        set("long", "夺工[2;37;0m
它是花样械的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "huangb");
        set("owner_name", "花样械");
        set_temp("owner", "huangb");
        set_temp("owner_name", "花样械");
        ::setup();
}
