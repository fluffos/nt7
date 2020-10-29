// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m依[1;32m雀[2;37;0m[2;37;0m", ({"yique"}));        
        set("gender", "女性");                
        set("long", "雀雀。。。[2;37;0m
它是依依的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yiyi");
        set("owner_name", "依依");
        set_temp("owner", "yiyi");
        set_temp("owner_name", "依依");
        ::setup();
}
