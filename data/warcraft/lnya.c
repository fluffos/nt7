// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哥的麒麟[2;37;0m[2;37;0m", ({"lnyaride"}));        
        set("gender", "男性");                
        set("long", "哥的麒麟[2;37;0m
它是龙里哥的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lnya");
        set("owner_name", "龙里哥");
        set_temp("owner", "lnya");
        set_temp("owner_name", "龙里哥");
        ::setup();
}
