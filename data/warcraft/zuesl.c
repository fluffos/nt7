// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m理论[2;37;0m[2;37;0m", ({"zuesls"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是贼就的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zuesl");
        set("owner_name", "贼就");
        set_temp("owner", "zuesl");
        set_temp("owner_name", "贼就");
        ::setup();
}
