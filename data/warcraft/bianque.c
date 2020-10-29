// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"caca"}));        
        set("gender", "女性");                
        set("long", "麒麟[2;37;0m
它是扁鹊的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "bianque");
        set("owner_name", "扁鹊");
        set_temp("owner", "bianque");
        set_temp("owner_name", "扁鹊");
        ::setup();
}
