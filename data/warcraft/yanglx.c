// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"hql"}));        
        set("gender", "男性");                
        set("long", "这是十龙十象的火麒麟。[2;37;0m
它是十龙十象的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yanglx");
        set("owner_name", "十龙十象");
        set_temp("owner", "yanglx");
        set_temp("owner_name", "十龙十象");
        ::setup();
}
