// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("空无可厚非[2;37;0m[2;37;0m", ({"qilinc"}));        
        set("gender", "男性");                
        set("long", "  [2;37;0m
它是雪丙的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xueshanc");
        set("owner_name", "雪丙");
        set_temp("owner", "xueshanc");
        set_temp("owner_name", "雪丙");
        ::setup();
}
