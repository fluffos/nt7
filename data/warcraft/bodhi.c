// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m菩提[2;37;0m[2;37;0m", ({"puti"}));        
        set("gender", "女性");                
        set("long", "菩提本无树[2;37;0m
它是须菩提的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "bodhi");
        set("owner_name", "须菩提");
        set_temp("owner", "bodhi");
        set_temp("owner_name", "须菩提");
        ::setup();
}
