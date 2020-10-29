// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "圣光闪闪[2;37;0m
它是曲塔马蒂的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qutmd");
        set("owner_name", "曲塔马蒂");
        set_temp("owner", "qutmd");
        set_temp("owner_name", "曲塔马蒂");
        ::setup();
}
