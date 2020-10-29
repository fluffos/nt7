// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[37m[31m神马[2;37;0m[2;37;0m", ({"zuesms"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是祖神马的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zuesm");
        set("owner_name", "祖神马");
        set_temp("owner", "zuesm");
        set_temp("owner_name", "祖神马");
        ::setup();
}
