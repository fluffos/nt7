// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("电单车[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "新能源电单车，无需充电日行千里。[2;37;0m
它是小偷的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "thief");
        set("owner_name", "小偷");
        set_temp("owner", "thief");
        set_temp("owner_name", "小偷");
        ::setup();
}
