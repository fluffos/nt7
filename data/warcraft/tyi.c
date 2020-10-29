// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞天[2;37;0m[2;37;0m", ({"flying"}));        
        set("gender", "女性");                
        set("long", "一天到晚不停地飞[2;37;0m
它是天意的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tyi");
        set("owner_name", "天意");
        set_temp("owner", "tyi");
        set_temp("owner_name", "天意");
        ::setup();
}
