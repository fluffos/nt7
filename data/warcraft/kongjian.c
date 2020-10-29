// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("是得分王[2;37;0m[2;37;0m", ({"sdfwer"}));        
        set("gender", "男性");                
        set("long", "是得分王[2;37;0m
它是在空的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kongjian");
        set("owner_name", "在空");
        set_temp("owner", "kongjian");
        set_temp("owner_name", "在空");
        ::setup();
}
