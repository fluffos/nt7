// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m粉木耳[2;37;0m[2;37;0m", ({"fenmuer"}));        
        set("gender", "女性");                
        set("long", "粉木耳[2;37;0m
它是酒妹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jiumei");
        set("owner_name", "酒妹");
        set_temp("owner", "jiumei");
        set_temp("owner_name", "酒妹");
        ::setup();
}
