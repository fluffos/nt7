// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("思密达[2;37;0m[2;37;0m", ({"super"}));        
        set("gender", "男性");                
        set("long", "哟哟，苍茫的天涯是我的爱[2;37;0m
它是欧阳弗血的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "skills");
        set("owner_name", "欧阳弗血");
        set_temp("owner", "skills");
        set_temp("owner_name", "欧阳弗血");
        ::setup();
}
