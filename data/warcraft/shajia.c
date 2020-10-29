// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m小蕾[2;37;0m[2;37;0m", ({"xiaolei"}));        
        set("gender", "男性");                
        set("long", "日行千里[2;37;0m
它是沙加的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "shajia");
        set("owner_name", "沙加");
        set_temp("owner", "shajia");
        set_temp("owner_name", "沙加");
        ::setup();
}
