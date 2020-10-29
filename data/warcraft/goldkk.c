// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("狗[2;37;0m[2;37;0m", ({"goldkkk"}));        
        set("gender", "男性");                
        set("long", "狗[2;37;0m
它是金狗的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldkk");
        set("owner_name", "金狗");
        set_temp("owner", "goldkk");
        set_temp("owner_name", "金狗");
        ::setup();
}
