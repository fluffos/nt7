// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("百科[2;37;0m[2;37;0m", ({"data"}));        
        set("gender", "女性");                
        set("long", "一只麒麟[2;37;0m
它是欧祥的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "opus");
        set("owner_name", "欧祥");
        set_temp("owner", "opus");
        set_temp("owner_name", "欧祥");
        ::setup();
}
