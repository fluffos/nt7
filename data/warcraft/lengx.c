// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("呼呼[2;37;0m[2;37;0m", ({"huhu"}));        
        set("gender", "男性");                
        set("long", "呼呼[2;37;0m
它是冷霄的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lengx");
        set("owner_name", "冷霄");
        set_temp("owner", "lengx");
        set_temp("owner_name", "冷霄");
        ::setup();
}
