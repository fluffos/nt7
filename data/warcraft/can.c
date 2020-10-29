// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m麒麟兽[2;37;0m[2;37;0m", ({"car"}));        
        set("gender", "男性");                
        set("long", "好可爱哦，像头狮子么。。。。[2;37;0m
它是铁血呆呆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "can");
        set("owner_name", "铁血呆呆");
        set_temp("owner", "can");
        set_temp("owner_name", "铁血呆呆");
        ::setup();
}
