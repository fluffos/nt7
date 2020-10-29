// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("费飞翔[2;37;0m[2;37;0m", ({"xixifff"}));        
        set("gender", "女性");                
        set("long", "自由的飞翔[2;37;0m
它是习费的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xixif");
        set("owner_name", "习费");
        set_temp("owner", "xixif");
        set_temp("owner_name", "习费");
        ::setup();
}
