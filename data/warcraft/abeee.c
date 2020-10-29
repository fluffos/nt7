// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m毛驴[2;37;0m[2;37;0m", ({"maolv"}));        
        set("gender", "女性");                
        set("long", "$HIY$毛驴[2;37;0m
它是苦力五号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "abeee");
        set("owner_name", "苦力五号");
        set_temp("owner", "abeee");
        set_temp("owner_name", "苦力五号");
        ::setup();
}
