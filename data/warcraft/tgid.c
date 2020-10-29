// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("无限制[2;37;0m[2;37;0m", ({"tgidd"}));        
        set("gender", "男性");                
        set("long", "你自己猜[2;37;0m
它是段硫磺的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tgid");
        set("owner_name", "段硫磺");
        set_temp("owner", "tgid");
        set_temp("owner_name", "段硫磺");
        ::setup();
}
