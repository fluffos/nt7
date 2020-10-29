// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("呜呜[2;37;0m[2;37;0m", ({"wwu"}));        
        set("gender", "女性");                
        set("long", "呜呜[2;37;0m
它是阿舞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "awu");
        set("owner_name", "阿舞");
        set_temp("owner", "awu");
        set_temp("owner_name", "阿舞");
        ::setup();
}
