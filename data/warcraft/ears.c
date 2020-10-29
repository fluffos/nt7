// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[32m星云锁莲[2;37;0m[2;37;0m", ({"fuyvan"}));        
        set("gender", "男性");                
        set("long", "兽合一[2;37;0m
它是一耳屎的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ears");
        set("owner_name", "一耳屎");
        set_temp("owner", "ears");
        set_temp("owner_name", "一耳屎");
        ::setup();
}
