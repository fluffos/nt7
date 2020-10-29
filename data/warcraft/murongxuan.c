// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("光明麒麟[2;37;0m[2;37;0m", ({"murongxuanride"}));        
        set("gender", "男性");                
        set("long", "光明麒麟[2;37;0m
它是慕容光明的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "murongxuan");
        set("owner_name", "慕容光明");
        set_temp("owner", "murongxuan");
        set_temp("owner_name", "慕容光明");
        ::setup();
}
