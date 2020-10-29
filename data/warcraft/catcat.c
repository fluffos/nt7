// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("究极体麒麟[2;37;0m[2;37;0m", ({"jinhu"}));        
        set("gender", "男性");                
        set("long", "究极体麒麟[2;37;0m
它是慕容长空的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "catcat");
        set("owner_name", "慕容长空");
        set_temp("owner", "catcat");
        set_temp("owner_name", "慕容长空");
        ::setup();
}
