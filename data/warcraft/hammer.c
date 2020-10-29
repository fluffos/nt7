// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("榔榔[1;37m[2;37;0m[2;37;0m", ({"lang"}));        
        set("gender", "女性");                
        set("long", "额[2;37;0m
它是榔头的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hammer");
        set("owner_name", "榔头");
        set_temp("owner", "hammer");
        set_temp("owner_name", "榔头");
        ::setup();
}
