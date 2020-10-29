// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("因量[2;37;0m[2;37;0m", ({"ldldld"}));        
        set("gender", "男性");                
        set("long", "胆大[2;37;0m
它是胃轱辘的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "wacaib");
        set("owner_name", "胃轱辘");
        set_temp("owner", "wacaib");
        set_temp("owner_name", "胃轱辘");
        ::setup();
}
