// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m毛驴[2;37;0m[2;37;0m", ({"maolv"}));        
        set("gender", "女性");                
        set("long", "$HIY$毛驴[2;37;0m
它是苦力十号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "abjjj");
        set("owner_name", "苦力十号");
        set_temp("owner", "abjjj");
        set_temp("owner_name", "苦力十号");
        ::setup();
}
