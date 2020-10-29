// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("学步车[2;37;0m[2;37;0m", ({"girlioi"}));        
        set("gender", "男性");                
        set("long", "学步车[2;37;0m
它是练习的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sshk");
        set("owner_name", "练习");
        set_temp("owner", "sshk");
        set_temp("owner_name", "练习");
        ::setup();
}
