// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"sucan"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是苏灿的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "suqier");
        set("owner_name", "苏灿");
        set_temp("owner", "suqier");
        set_temp("owner_name", "苏灿");
        ::setup();
}
