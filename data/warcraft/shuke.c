// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "一头麒麟[2;37;0m
它是舒克的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "shuke");
        set("owner_name", "舒克");
        set_temp("owner", "shuke");
        set_temp("owner_name", "舒克");
        ::setup();
}
