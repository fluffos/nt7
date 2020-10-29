// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("拜依依[2;37;0m[2;37;0m", ({"zizibbb"}));        
        set("gender", "女性");                
        set("long", "自由的飞翔[2;37;0m
它是姿拜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zizib");
        set("owner_name", "姿拜");
        set_temp("owner", "zizib");
        set_temp("owner_name", "姿拜");
        ::setup();
}
