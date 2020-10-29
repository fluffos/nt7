// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("三[2;37;0m[2;37;0m", ({"jiba"}));        
        set("gender", "男性");                
        set("long", "三[2;37;0m
它是不想的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dupengqm");
        set("owner_name", "不想");
        set_temp("owner", "dupengqm");
        set_temp("owner_name", "不想");
        ::setup();
}
