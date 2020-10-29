// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "麒麟[2;37;0m
它是钱三的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldc");
        set("owner_name", "钱三");
        set_temp("owner", "goldc");
        set_temp("owner_name", "钱三");
        ::setup();
}
