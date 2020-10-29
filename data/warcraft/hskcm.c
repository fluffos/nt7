// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀儿[2;37;0m[2;37;0m", ({"hongniao"}));        
        set("gender", "男性");                
        set("long", "朱雀儿[2;37;0m
它是康皓阳的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hskcm");
        set("owner_name", "康皓阳");
        set_temp("owner", "hskcm");
        set_temp("owner_name", "康皓阳");
        ::setup();
}
