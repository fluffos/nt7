// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("沙兽[2;37;0m[2;37;0m", ({"shashou"}));        
        set("gender", "男性");                
        set("long", "沙兽[2;37;0m
它是沙虫的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "shachong");
        set("owner_name", "沙虫");
        set_temp("owner", "shachong");
        set_temp("owner_name", "沙虫");
        ::setup();
}
