// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;35m七窍[2;37;0m[1;32m通了[5m[1;31m六窍[2;37;0m[2;37;0m[2;37;0m", ({"noob"}));        
        set("gender", "男性");                
        set("long", "七窍只是通了六窍，还有一窍不通。[2;37;0m
它是一窍不通的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "rookie");
        set("owner_name", "一窍不通");
        set_temp("owner", "rookie");
        set_temp("owner_name", "一窍不通");
        ::setup();
}
