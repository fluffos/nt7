// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("兔[2;37;0m[2;37;0m", ({"goldddd"}));        
        set("gender", "男性");                
        set("long", "兔[2;37;0m
它是金兔的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "golddd");
        set("owner_name", "金兔");
        set_temp("owner", "golddd");
        set_temp("owner_name", "金兔");
        ::setup();
}
