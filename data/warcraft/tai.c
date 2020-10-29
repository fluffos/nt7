// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m仙鹤[2;37;0m[2;37;0m", ({"car"}));        
        set("gender", "男性");                
        set("long", "$HIY$仙鹤[2;37;0m
它是太上老君的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tai");
        set("owner_name", "太上老君");
        set_temp("owner", "tai");
        set_temp("owner_name", "太上老君");
        ::setup();
}
