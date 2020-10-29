// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("羽毛[2;37;0m[2;37;0m", ({"qietee"}));        
        set("gender", "女性");                
        set("long", "一只乖巧的麒麟[2;37;0m
它是银海的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "etee");
        set("owner_name", "银海");
        set_temp("owner", "etee");
        set_temp("owner_name", "银海");
        ::setup();
}
