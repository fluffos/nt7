// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m记录点[2;37;0m[2;37;0m", ({"teak_save"}));        
        set("gender", "女性");                
        set("long", "$BLK$记录点[2;37;0m
它是身正的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mmm");
        set("owner_name", "身正");
        set_temp("owner", "mmm");
        set_temp("owner_name", "身正");
        ::setup();
}
