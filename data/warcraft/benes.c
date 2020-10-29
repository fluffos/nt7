// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("东东[2;37;0m[2;37;0m", ({"dongdong"}));        
        set("gender", "女性");                
        set("long", "一只朱雀[2;37;0m
它是林丰的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "benes");
        set("owner_name", "林丰");
        set_temp("owner", "benes");
        set_temp("owner_name", "林丰");
        ::setup();
}
