// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("兔尾巴[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "兔尾巴[2;37;0m
它是生肖兔的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zood");
        set("owner_name", "生肖兔");
        set_temp("owner", "zood");
        set_temp("owner_name", "生肖兔");
        ::setup();
}
