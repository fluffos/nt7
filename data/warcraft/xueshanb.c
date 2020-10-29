// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("色无可厚非[2;37;0m[2;37;0m", ({"qilinb"}));        
        set("gender", "女性");                
        set("long", "  [2;37;0m
它是雪乙的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xueshanb");
        set("owner_name", "雪乙");
        set_temp("owner", "xueshanb");
        set_temp("owner_name", "雪乙");
        ::setup();
}
