// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m紫玉麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "look[2;37;0m
它是重小橙的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "woacso");
        set("owner_name", "重小橙");
        set_temp("owner", "woacso");
        set_temp("owner_name", "重小橙");
        ::setup();
}
