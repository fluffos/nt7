// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老狗欧尚[2;37;0m[2;37;0m", ({"lgos"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是老狗哦的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lgo");
        set("owner_name", "老狗哦");
        set_temp("owner", "lgo");
        set_temp("owner_name", "老狗哦");
        ::setup();
}
