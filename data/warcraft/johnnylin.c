// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m胡麒麟[2;37;0m[2;37;0m", ({"johnnydragon"}));        
        set("gender", "男性");                
        set("long", "This is JohnnyDragon ![2;37;0m
它是胡一刀的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "johnnylin");
        set("owner_name", "胡一刀");
        set_temp("owner", "johnnylin");
        set_temp("owner_name", "胡一刀");
        ::setup();
}
