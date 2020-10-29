// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("灵雀[2;37;0m[2;37;0m", ({"sss"}));        
        set("gender", "女性");                
        set("long", "海妮娜的灵兽[2;37;0m
它是海妮娜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "nina");
        set("owner_name", "海妮娜");
        set_temp("owner", "nina");
        set_temp("owner_name", "海妮娜");
        ::setup();
}
