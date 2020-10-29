// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("孔雀[2;37;0m[2;37;0m", ({"perform_bihai"}));        
        set("gender", "女性");                
        set("long", "孔[2;37;0m
它是桔皮的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jupi");
        set("owner_name", "桔皮");
        set_temp("owner", "jupi");
        set_temp("owner_name", "桔皮");
        ::setup();
}
