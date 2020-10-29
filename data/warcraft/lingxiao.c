// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("咳[2;37;0m[2;37;0m", ({"kei"}));        
        set("gender", "男性");                
        set("long", "咳[2;37;0m
它是凌霄的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lingxiao");
        set("owner_name", "凌霄");
        set_temp("owner", "lingxiao");
        set_temp("owner_name", "凌霄");
        ::setup();
}
