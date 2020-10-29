// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"wjzz"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是维剑君的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wjz");
        set("owner_name", "维剑君");
        set_temp("owner", "wjz");
        set_temp("owner_name", "维剑君");
        ::setup();
}
