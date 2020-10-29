// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m朱雀[2;37;0m[2;37;0m", ({"zhus"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是露淫甲的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "luren");
        set("owner_name", "露淫甲");
        set_temp("owner", "luren");
        set_temp("owner_name", "露淫甲");
        ::setup();
}
