// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("次飞翔[2;37;0m[2;37;0m", ({"xixiccc"}));        
        set("gender", "女性");                
        set("long", "自由的飞翔[2;37;0m
它是习赐的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xixic");
        set("owner_name", "习赐");
        set_temp("owner", "xixic");
        set_temp("owner_name", "习赐");
        ::setup();
}
