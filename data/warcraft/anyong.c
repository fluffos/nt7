// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟兽[2;37;0m[2;37;0m", ({"qilinshou"}));        
        set("gender", "男性");                
        set("long", "攻击坐骑[2;37;0m
它是暗涌的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "anyong");
        set("owner_name", "暗涌");
        set_temp("owner", "anyong");
        set_temp("owner_name", "暗涌");
        ::setup();
}
