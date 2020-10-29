// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("三[2;37;0m[2;37;0m", ({"wolf"}));        
        set("gender", "女性");                
        set("long", "如狼却又如狗的动物[2;37;0m
它是玖流的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wingking");
        set("owner_name", "玖流");
        set_temp("owner", "wingking");
        set_temp("owner_name", "玖流");
        ::setup();
}
