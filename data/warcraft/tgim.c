// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"tgimmm"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是无限之力的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "tgim");
        set("owner_name", "无限之力");
        set_temp("owner", "tgim");
        set_temp("owner_name", "无限之力");
        ::setup();
}
