// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m毛驴[2;37;0m[2;37;0m", ({"maolv"}));        
        set("gender", "女性");                
        set("long", "毛驴[2;37;0m
它是苦力二号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "abbbb");
        set("owner_name", "苦力二号");
        set_temp("owner", "abbbb");
        set_temp("owner_name", "苦力二号");
        ::setup();
}
