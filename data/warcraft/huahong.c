// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m大黄牛[2;37;0m[2;37;0m", ({"huahongs"}));        
        set("gender", "男性");                
        set("long", "$BLINK$$HIY$大黄牛[2;37;0m
它是花红的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "huahong");
        set("owner_name", "花红");
        set_temp("owner", "huahong");
        set_temp("owner_name", "花红");
        ::setup();
}
