// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ddqq"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是堂钱的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ddq");
        set("owner_name", "堂钱");
        set_temp("owner", "ddq");
        set_temp("owner_name", "堂钱");
        ::setup();
}
