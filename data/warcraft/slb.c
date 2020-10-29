// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m麒麟[2;37;0m[2;37;0m", ({"niao"}));        
        set("gender", "女性");                
        set("long", "麒麟[2;37;0m
它是汀汀婕的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "slb");
        set("owner_name", "汀汀婕");
        set_temp("owner", "slb");
        set_temp("owner_name", "汀汀婕");
        ::setup();
}
