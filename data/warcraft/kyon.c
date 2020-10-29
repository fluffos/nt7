// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("炽翼[2;37;0m[2;37;0m", ({"puppy"}));        
        set("gender", "男性");                
        set("long", "red[2;37;0m
它是浪还潮的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kyon");
        set("owner_name", "浪还潮");
        set_temp("owner", "kyon");
        set_temp("owner_name", "浪还潮");
        ::setup();
}
