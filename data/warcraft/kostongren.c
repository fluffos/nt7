// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("美丽中国梦[2;37;0m[2;37;0m", ({"kostongrenpet"}));        
        set("gender", "男性");                
        set("long", "$HIB$仓库铜人[2;37;0m
它是铜人仓库的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kostongren");
        set("owner_name", "铜人仓库");
        set_temp("owner", "kostongren");
        set_temp("owner_name", "铜人仓库");
        ::setup();
}
