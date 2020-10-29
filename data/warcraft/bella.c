// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m金毛[1;34m狼王[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "kick[2;37;0m
它是伊莎贝拉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "bella");
        set("owner_name", "伊莎贝拉");
        set_temp("owner", "bella");
        set_temp("owner_name", "伊莎贝拉");
        ::setup();
}
