// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("风云再起[2;37;0m[2;37;0m", ({"yifeng"}));        
        set("gender", "男性");                
        set("long", "风云再起[2;37;0m
它是楚易风的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "chuyifeng");
        set("owner_name", "楚易风");
        set_temp("owner", "chuyifeng");
        set_temp("owner_name", "楚易风");
        ::setup();
}
