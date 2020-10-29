// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "神光闪闪[2;37;0m
它是曲妮马蒂的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qunmd");
        set("owner_name", "曲妮马蒂");
        set_temp("owner", "qunmd");
        set_temp("owner_name", "曲妮马蒂");
        ::setup();
}
