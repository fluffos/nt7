// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("云和风[2;37;0m[2;37;0m", ({"lms"}));        
        set("gender", "男性");                
        set("long", "一只朱雀[2;37;0m
它是愈林的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ofdm");
        set("owner_name", "愈林");
        set_temp("owner", "ofdm");
        set_temp("owner_name", "愈林");
        ::setup();
}
