// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("士大夫[2;37;0m[2;37;0m", ({"odi"}));        
        set("gender", "男性");                
        set("long", "士大夫[2;37;0m
它是王大汗的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zilei");
        set("owner_name", "王大汗");
        set_temp("owner", "zilei");
        set_temp("owner_name", "王大汗");
        ::setup();
}
