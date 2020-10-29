// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m草泥马[2;37;0m[2;37;0m[2;37;0m", ({"nima"}));        
        set("gender", "女性");                
        set("long", "这是一只羊驼！[2;37;0m
它是段思平的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "six");
        set("owner_name", "段思平");
        set_temp("owner", "six");
        set_temp("owner_name", "段思平");
        ::setup();
}
