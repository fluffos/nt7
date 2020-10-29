// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("智慧神兽[2;37;0m[2;37;0m", ({"jinhu"}));        
        set("gender", "男性");                
        set("long", "智慧神兽[2;37;0m
它是武当飞二的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "catb");
        set("owner_name", "武当飞二");
        set_temp("owner", "catb");
        set_temp("owner_name", "武当飞二");
        ::setup();
}
