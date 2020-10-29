// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qwes"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是硫磺桃花的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tgit");
        set("owner_name", "硫磺桃花");
        set_temp("owner", "tgit");
        set_temp("owner_name", "硫磺桃花");
        ::setup();
}
